/**
 * @file gokand/sensorimpliio.cpp
 * @brief A IIO sensor device back end implementation class.
 */
/* 
 * Copyright 2014 Canonical Ltd.
 * 
 * Phasia is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISFACTORY
 * QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gokand/sensorimpliio.h"

#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <libudev.h>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

using namespace std;


namespace Gokand
{

typedef unique_ptr<udev, udev*(*)(udev*)>                      UdevPtr;
typedef unique_ptr<udev_device, udev_device*(*)(udev_device*)> UdevDevicePtr;
typedef vector<UdevDevicePtr>                                  UdevDevicePtrList;

static const string device_key = "iio:device";
static const string trigger_key = "trigger";
static const string channel_enable_suffix = "_en";
static const string channel_index_suffix  = "_index";
static const string channel_type_suffix   = "_type";
static const string channel_trigger_suffix = "/trigger/current_trigger";
static const string channel_length_suffix = "/buffer/length";
static const string channel_buffer_suffix = "/buffer/enable";
static const string channel_subdir = "/scan_elements/";


static bool
read_is_channel_enabled(string channel_root_path)
{
  unsigned is_enabled = 0;
  ifstream enable_file(channel_root_path.append(channel_enable_suffix));
  if (enable_file)
  {
    enable_file >> is_enabled;
  }
  return is_enabled;
}


static void
write_channel_enabled(string channel_root_path, bool is_enabled)
{
  ofstream enable_file(channel_root_path.append(channel_enable_suffix));
  enable_file << (is_enabled ? '1' : '0');
}


static unsigned
read_channel_index(string channel_root_path)
{
  unsigned index = 0;
  ifstream index_file(channel_root_path.append(channel_index_suffix));
  if (index_file)
  {
    index_file >> index;
  }
  return index;
}


/**
 * Gets a float-valued parameter frmo the channel.
 * @param[in] param_name
 * @param[in] device_path
 * @param[in] channel_name
 * @param[in] default_value
 *
 * The rules for finding the parameter description appear to be somewhat baroque
 * and possibly vary from device to device and kernel version to kernel version.
 */
static float
read_channel_float_param(string const& param_name,
                         string const& device_path,
                         string const& channel_name,
                         float         default_value = 0.0f)
{
  float value = default_value;
  string channel_file_name = device_path + channel_subdir
    + channel_name
    + "_" + param_name;
  ifstream channel_file(channel_file_name);
  if (channel_file)
  {
    channel_file >> value;
  }
  else
  {
    string device_file_name = device_path + '/'
      + channel_name
      + "_" + param_name;
    ifstream device_file(device_file_name);
    if (device_file)
    {
      device_file >> value;
    }
    else
    {
      string generic_file_name = device_path + '/'
        + channel_name.substr(0, channel_name.rfind('_'))
        + "_" + param_name;
      ifstream generic_file(generic_file_name);
      if (generic_file)
      {
        generic_file >> value;
      }
    }
  }
  return value;
}


static void
read_channel_type(string    channel_root_path,
                  char&     endianness,
                  char&     signedness,
                  unsigned& bits,
                  unsigned& width,
                  unsigned& shift)
{
  string type_string;
  ifstream type_file(channel_root_path.append(channel_type_suffix));
  if (type_file)
  {
    type_file >> type_string;
  }
  istringstream istr(type_string);
  istr.get(endianness);
  istr.ignore(2);
  istr.get(signedness);
  istr >> bits;
  istr.ignore(1);
  istr >> width;
  istr.ignore(2);
  istr >> shift;
}


/**
 * Calculates the individual field offsets from the beginning of the output
 * buffer and returns the overall buffer width.
 *
 * Field width calculations assumes all field widths are evenly divisible by the
 * size of teh local byte.
 */
static size_t
calculate_buffer_offsets(vector<IIOChannelInfo>& channel_info)
{
  sort(begin(channel_info), end(channel_info),
            [](IIOChannelInfo const& lhs, IIOChannelInfo const& rhs){ return lhs.index_ < rhs.index_; });

  unsigned offset = 0;
  for (auto& ci: channel_info)
  {
    ci.ob_offset_ = offset / CHAR_BIT;
    offset += ci.ob_width_;
  }
  return offset / CHAR_BIT;
}

void SensorImplIIO::
enable_trigger()
{
  string trigger_file_name = syspath_ + channel_trigger_suffix;
  ofstream trigger_file(trigger_file_name);
  if (!trigger_file) cerr << "error " << errno << " opening " << trigger_file_name << ": " << strerror(errno) << "\n";
  if (trigger_file) trigger_file << trigger_name_;
}


void SensorImplIIO::
disable_trigger()
{
  string trigger_file_name = syspath_ + channel_trigger_suffix;
  ofstream trigger_file(trigger_file_name);
  if (!trigger_file) cerr << "error " << errno << " opening " << trigger_file_name << ": " << strerror(errno) << "\n";
  if (trigger_file) trigger_file << "none";
}


void SensorImplIIO::
enable_buffer()
{
  string length_file_name = syspath_ + channel_length_suffix;
  ofstream length_file(length_file_name);
  if (!length_file) cerr << "error " << errno << " opening " << length_file_name << ": " << strerror(errno) << "\n";
  if (length_file) length_file << buffer_length_;
  string buffer_file_name = syspath_ + channel_buffer_suffix;
  ofstream buffer_file(buffer_file_name);
  if (!buffer_file) cerr << "error " << errno << " opening " << buffer_file_name << ": " << strerror(errno) << "\n";
  if (buffer_file) buffer_file << '1';
}


void SensorImplIIO::
disable_buffer()
{
  string buffer_file_name = syspath_ + channel_buffer_suffix;
  ofstream buffer_file(buffer_file_name);
  if (!buffer_file) cerr << "error " << errno << " opening " << buffer_file_name << ": " << strerror(errno) << "\n";
  if (buffer_file) buffer_file << '0';
}


SensorImplIIO::
SensorImplIIO(udev_device* dev)
: name_(udev_device_get_sysattr_value(dev, "name"))
, syspath_(udev_device_get_syspath(dev))
, devnode_(udev_device_get_devnode(dev))
, buffer_length_(128)
, fd_(-1)
{
  string channel_dir = syspath_ + channel_subdir;
  DIR *dp;
  dp = opendir(channel_dir.c_str());
  if (!dp)
  {
    cerr << "error " << errno << " opening '" << channel_dir << "': " << strerror(errno) << "\n";
  }
  else
  {
    const struct dirent *ent;
    while ((ent = readdir(dp))) {
      string filename = ent->d_name;
      if (filename.length() > channel_enable_suffix.length()
          && 0 == filename.compare(filename.length() - channel_enable_suffix.length(),
                                   channel_enable_suffix.length(),
                                   channel_enable_suffix))
      {
        string channel_name = filename.substr(0, filename.length() - channel_enable_suffix.length());
        string channel_root_path = channel_dir + "/" + channel_name;
        unsigned index = read_channel_index(channel_root_path);
        float    scale = read_channel_float_param("scale", syspath_, channel_name, 1.0f);
        float    offset = read_channel_float_param("offset", syspath_, channel_name, 0.0f);
        char     endianness;
        char     signedness;
        unsigned bits;
        unsigned width;
        unsigned shift;
        bool     is_enabled = read_is_channel_enabled(channel_root_path);
        read_channel_type(channel_root_path, endianness, signedness, bits, width, shift);

        channel_info_.push_back({channel_name, index, is_enabled, scale, offset, endianness, signedness, 0, width, bits, shift });
      }
    }
    closedir(dp);
  }
  packet_length_ = calculate_buffer_offsets(channel_info_);
}


SensorImplIIO::
~SensorImplIIO()
{ }


void SensorImplIIO::
add_trigger_device(udev_device* dev)
{
  trigger_name_ = udev_device_get_sysattr_value(dev, "name");
}


string const& SensorImplIIO::
name() const
{
  return name_;
}


void SensorImplIIO::
enable()
{
  string channel_dir = syspath_ + channel_subdir;
  for (auto const& channel: channel_info_)
  {
    write_channel_enabled(channel_dir + channel.name_, true);
  }
}


void SensorImplIIO::
disable() 
{
  string channel_dir = syspath_ + channel_subdir;
  for (auto const& channel: channel_info_)
  {
    write_channel_enabled(channel_dir + channel.name_, false);
  }
}


int SensorImplIIO::
open()
{
  if (fd_ == -1)
  {
    enable_trigger();
    enable_buffer();
    fd_ = ::open(devnode_.c_str(), O_RDONLY | O_CLOEXEC | O_NONBLOCK);
  }
  return fd_;

}


void SensorImplIIO::
close()
{
  ::close(fd_);
  fd_ = -1;
  disable_buffer();
  disable_trigger();
}


ostream& SensorImplIIO::
print(ostream& ostr)
{
  ostr << name_ << " devnode='" << devnode_ << "' syspath='" << syspath_ << "'\n";
  ostr << "  trigger " << trigger_name_ << "\n";
  ostr << "  packet_length=" << packet_length_ << "\n";
  for (auto const& channel: channel_info_)
  {
    ostr << "   channel " << channel.name_
         << "   index=" << channel.index_
         << "   is_enabled=" << channel.is_enabled_
         << "   si_scale=" << channel.si_scale_
         << "   si_offset=" << channel.si_offset_
         << "   ob_endianness=" << channel.ob_endianness_
         << "   ob_signedness=" << channel.ob_signedness_
         << "   ob_offset=" << channel.ob_offset_
         << "   ob_width=" << channel.ob_width_
         << "   ob_bits=" << channel.ob_bits_
         << "   ob_shift=" << channel.ob_shift_
         << "\n";
  }
  return ostr;
}


/**
 * Creates a udev context object.
 *
 * @throws std::runtime_error if the udev context can not be created.
 */
static UdevPtr
create_udev_ctxt()
{
  UdevPtr udev_ctxt(udev_new(), &udev_unref);
  if (!udev_ctxt)
  {
    throw runtime_error("can not create udev instance");
  }
  return udev_ctxt;
}


/**
 * Creates a (smart pointer to a) udev device..
 * @param[in] udev_ctxt A valid udev context object.
 * @param[in] path      The path to the udev device entry.
 */
static UdevDevicePtr
create_udev_device(UdevPtr const& udev_ctxt, char const* path)
{
    UdevDevicePtr device(udev_device_new_from_syspath(udev_ctxt.get(), path),
                         udev_device_unref);
    return device;
}


/**
 * An object that enumerates IIO devices in the sysfs tree.
 */
class UdevDeviceEnumerator
{
public:
  UdevDeviceEnumerator(UdevPtr const& udev_ctxt)
  : enumerator_(udev_enumerate_new(udev_ctxt.get()))
  {
    if (!enumerator_)
    {
      throw runtime_error("can not create udev instance");
    }
  }

  ~UdevDeviceEnumerator()
  { udev_enumerate_unref(enumerator_); }

  UdevDevicePtrList
  discover_devices(UdevPtr const& udev_ctxt)
  {
    UdevDevicePtrList iio_devs;

    udev_enumerate_add_match_subsystem(enumerator_, "iio");
    udev_enumerate_scan_devices(enumerator_);
    for (udev_list_entry* device = udev_enumerate_get_list_entry(enumerator_);
         device;
         device = udev_list_entry_get_next(device))
    {
      char const* path = udev_list_entry_get_name(device);
      iio_devs.push_back(create_udev_device(udev_ctxt, path));
    }
    return iio_devs;
  }

private:
  udev_enumerate* enumerator_;
};


/**
 * Enumerates sensor devices found by the kernel.
 * @param[out] sensors  A collection of enumerated sensor devices.
 */
void
autodetect_iio_devices(Sensor::Bag& sensors)
{
  UdevPtr udev_ctxt{ create_udev_ctxt() };
  UdevDeviceEnumerator enumerator(udev_ctxt);
  UdevDevicePtrList iio_devs{ enumerator.discover_devices(udev_ctxt) };

  for (auto const& pdev: iio_devs)
  {
    string sysname(udev_device_get_sysname(pdev.get()));
    if (0 == sysname.find(device_key))
    {
      int device_index = stoi(sysname.substr(device_key.length()));
      SensorImplIIO* iio_dev_ptr = new SensorImplIIO(pdev.get());
      for (auto const& tdev: iio_devs)
      {
        string trigger_sysname(udev_device_get_sysname(tdev.get()));
        if (0 == trigger_sysname.find(trigger_key))
        {
          int trigger_index = stoi(trigger_sysname.substr(trigger_key.length()));
          if (trigger_index == device_index)
          {
            iio_dev_ptr->add_trigger_device(tdev.get());
          }
        }
      }

      sensors.push_back(create_sensor_with_impl(iio_dev_ptr));
    }
  }
}

} // namspace Gokand


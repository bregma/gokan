/**
 * @file libgokan/device.h
 * @brief A system sensor device class.
 */
/* 
 * Copyright 2014 Canonical Ltd.
 * 
 * Phasia is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISDEVICE
 * QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGOKAN_DEVICE_H_
#define LIBGOKAN_DEVICE_H_

#include <memory>
#include <vector>


namespace Gokan
{


/**
 * A base class for various sensor devices.
 */
class Device
{
public:
  /** Devices are handled internally by a unique identifier.  */
  typedef int Id;

  /** Human-readable device type.  */
  typedef std::string Type;

  /** An owning smart pointer to a sensor device.  */
  typedef std::shared_ptr<Device> Ptr;

  /** A collection of sensor devices.  */
  typedef std::vector<Device::Ptr> Bag;

  /** An internal implmentation of the device. */
  struct Impl;

  /** An owning smart pointer to an internal sensor implementation.  */
  typedef std::unique_ptr<Device::Impl> ImplPtr;

public:
  explicit Device(Impl* impl);
  virtual ~Device();

  /** Gets the sensor's unique identifier.  */
  Device::Id
  id() const;

  /** Gets the autodetected type of the sensor.  */
  Device::Type
  type() const;

  /** Prepares the sensor device for reporting data.  */
  int
  open();

  /** Stops the reporting of data from te device.  */
  void
  close();

private:
  ImplPtr impl_;
};


/**
 * Fetches zero or more devices of a goven type.
 * @param[in] type  The type of the device(s) to get.
 */
Device::Bag
get_devices_by_type(Device::Type const& type);

} // namspace Gokan

#endif /* LIBGOKAN_DEVICE_H_*/


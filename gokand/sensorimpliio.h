/**
 * @file gokand/sensorimpliio.h
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
#ifndef GOKAND_SENSORIMPLIIO_H_
#define GOKAND_SENSORIMPLIIO_H_

#include "gokand/sensor.h"
#include "gokand/sensorimpl.h"


struct udev_device;


namespace Gokand
{
/**
 * Collected information on an IIO channel.
 *
 * Each device has one or more channels that can be controlled or report data.
 * This structure is an internal structure collecting information required to
 * manipulate or use the underlying channel.
 */
struct IIOChannelInfo
{
  std::string name_;           ///< the channel name
  unsigned    index_;          ///< the channel index in the buffer output
  bool        is_enabled_;     ///< indicates if the channel is currently enabled
  float       si_scale_;       ///< scale factor for conversion to SI units
  float       si_offset_;      ///< offset for conversion to SI units
  char        ob_endianness_;  ///< endianness of buffer data { b, l }
  char        ob_signedness_;  ///< signedness of buffer data { s, u }
  unsigned    ob_offset_;      ///< output buffer offset
  unsigned    ob_width_;       ///< output buffer field width
  unsigned    ob_bits_;        ///< output buffer data width
  unsigned    ob_shift_;       ///< output buffer shift width
};


/**
 * A sensor device implemented as an Industrial I/O device.
 */
class SensorImplIIO
: public SensorImpl
{
public:
  explicit
  SensorImplIIO(udev_device* dev);

  ~SensorImplIIO() override;

  void
  add_trigger_device(udev_device* dev);

  /** Gets the name of the device. */
  std::string const&
  name() const override;

  /** Enables the device for data detection. */
  void
  enable() override;

  /** Disables the device for data detection. */
  void
  disable() override;

  /** Opens a data connection to the device. */
  int
  open() override;

  /** Opens a data connection to the device. */
  void
  close() override;

  /** Writes descriptive information about the device to a stream. */
  std::ostream&
  print(std::ostream&) override;

private:
  void
  enable_trigger();

  void
  disable_trigger();

  void
  enable_buffer();

  void
  disable_buffer();

private:
  std::string                 name_;
  std::string                 syspath_;
  std::string                 devnode_;
  std::vector<IIOChannelInfo> channel_info_;
  std::string                 trigger_name_;
  size_t                      packet_length_;  ///< length of output buffer data
  size_t                      buffer_length_;  ///< length of kernel ring buffer
  int                         fd_;
};

void
autodetect_iio_devices(Sensor::Bag& sensors);

} // namspace Gokand

#endif /* GOKAND_SENSORIMPLIIO_H */

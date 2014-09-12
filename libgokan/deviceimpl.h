/**
 * @file libgokan/deviceimpl.h
 * @brief A system sensor device class internal implementation.
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
#ifndef LIBGOKAN_DEVICEIMPL_H_
#define LIBGOKAN_DEVICEIMPL_H_

#include "libgokan/device.h"


namespace Gokan
{


/**
 * A base class for various sensor devices.
 */
struct Device::Impl
{
public:
  Impl(Device::Id id, Device::Type const& type);

  ~Impl();

  /** Gets the sensor's unique identifier.  */
  Device::Id
  id() const;

  /** Gets the autodetected type of the sensor.  */
  Device::Type
  type() const;

private:
  Device::Id   id_;
  Device::Type type_;
};


} // namspace Gokan

#endif /* LIBGOKAN_DEVICEIMPL_H_*/


/**
 * @file libgokan/device.cpp
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
#include "libgokan/device.h"

#include "libgokan/deviceimpl.h"


namespace Gokan
{


Device::
Device(Impl* impl)
: impl_(impl)
{ }


Device::
~Device()
{ }


Device::Id Device::
id() const
{ return impl_->id(); }


Device::Type Device::
type() const
{ return impl_->type(); }


int Device::
open()
{ return impl_->open(); }


void Device::
close()
{ return impl_->close(); }


Device::Bag
get_devices_by_type(Device::Type const& type)
{
  Device::Bag devices;
  return devices;
}


} // namspace Gokan



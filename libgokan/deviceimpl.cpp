/**
 * @file libgokan/deviceimpl.cpp
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

#include "libgokan/deviceimpl.h"


namespace Gokan
{

Device::Impl::
Impl(Device::Id id, Device::Type const& type)
: id_(id)
, type_(type)
{ }


Device::Impl::
~Impl()
{ }


Device::Id Device::Impl::
id() const
{
  return id_;
}


Device::Type Device::Impl::
type() const
{
  return type_;
}

} // namspace Gokan



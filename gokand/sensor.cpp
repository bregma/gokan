/**
 * @file gokand/sensor.cpp
 * @brief A system sensor device class.
 */
/* 
 * Copyright 2014 Canonical Ltd.
 * 
 * Gokan is free software: you can redistribute it and/or modify it
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
#include "gokand/sensor.h"

#include "gokand/sensorimpl.h"


namespace Gokand
{

Sensor::
Sensor(Id id, std::unique_ptr<SensorImpl> impl)
: id_(id)
, impl_(std::move(impl))
{
}


Sensor::
~Sensor()
{
}


Sensor::Id Sensor::
id() const
{
  return id_;
}

Sensor::Type Sensor::
type() const
{
  return impl_->name();
}

void Sensor::
enable()
{
  impl_->enable();
}


void Sensor::
disable()
{
  impl_->disable();
}


int Sensor::
open()
{
  return impl_->open();
}


void Sensor::
close()
{
  impl_->close();
}


std::ostream&
operator<<(std::ostream& ostr, Sensor::Ptr const& sensor_device)
{
  return sensor_device->impl_->print(ostr);
}


Sensor::Ptr
create_sensor_with_impl(SensorImpl* impl)
{
  static Sensor::Id next_device_id = 100;
  return std::make_shared<Sensor>(next_device_id++, Sensor::ImplPtr(impl));
}


} // namspace Gokand


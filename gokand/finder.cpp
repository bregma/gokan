/**
 * @file gokand/finder.cpp
 * @brief gokand sensor device finder
 */

/*
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "gokand/finder.h"


namespace Gokand
{


struct Finder::Impl
{
  Impl(Configuration* configuration)
  : configuration_(configuration)
  { }

  Configuration* configuration_;
};


Finder::
Finder(Configuration* configuration)
: impl_(new Impl(configuration))
{ }


Finder::
~Finder()
{ }


Sensor::Bag Finder::
sensors_get_by_type(Sensor::Type const& sensor_type)
{
  Sensor::Bag sensor_bag;
  return sensor_bag;
}


} // namespace Gokand


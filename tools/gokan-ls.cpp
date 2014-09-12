/**
 * @file tools/gokan-ls
 * @brief Gokan sensor device lister tool
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

#include <iostream>
#include "libgokan/device.h"

using namespace Gokan;


int
main()
{
  Device::Bag devices = get_devices_by_type("all");
  for (auto const& device: devices)
  {
    std::cout << device->id() << ": " << device->type() << "\n";
  }
}


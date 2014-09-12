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

#include <iostream>
#include "libgokan/dbusinterface.h"
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
{
  GokanDevice* device = gokan_device_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
                                                            G_DBUS_PROXY_FLAGS_NONE,
                                                            "com.canonical.Gokan",
                                                            "/com/canonical/Gokan/Device",
                                                            nullptr,
                                                            nullptr);
  if (device)
  {
    if (gokan_device_call_start_read_sync(device, impl_->id(), nullptr, nullptr))
    {
      // do something here
    }
    else
    {
      std::cerr << "error starting read\n";
    }
    g_clear_object(&device);
  }
  else
  {
    std::cerr << "error getting finder\n";
  }
  return 0;
}


void Device::
close()
{
  GokanDevice* device = gokan_device_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
                                                            G_DBUS_PROXY_FLAGS_NONE,
                                                            "com.canonical.Gokan",
                                                            "/com/canonical/Gokan/Device",
                                                            nullptr,
                                                            nullptr);
  if (device)
  {
    if (gokan_device_call_stop_read_sync(device, impl_->id(), nullptr, nullptr))
    {
      // do something here
    }
    else
    {
      std::cerr << "error stopping read\n";
    }
    g_clear_object(&device);
  }
  else
  {
    std::cerr << "error getting finder\n";
  }
}


Device::Bag
get_devices_by_type(Device::Type const& type)
{
  Device::Bag devices;
  GokanFinder* finder = gokan_finder_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
                                                            G_DBUS_PROXY_FLAGS_NONE,
                                                            "com.canonical.Gokan",
                                                            "/com/canonical/Gokan/Finder",
                                                            nullptr,
                                                            nullptr);
  if (finder)
  {
    GVariant* sensors = nullptr;
    if (gokan_finder_call_sensors_get_by_type_sync(finder,
                                                   type.c_str(),
                                                   &sensors,
                                                   nullptr,
                                                   nullptr))
    {
      gsize count = g_variant_n_children(sensors);
      for (gsize i = 0; i < count; ++i)
      {
        GVariant* variant = g_variant_get_child_value(sensors, i);
        GVariant* vid = g_variant_get_child_value(variant, 0);
        GVariant* vname = g_variant_get_child_value(variant, 1);
        gint id = g_variant_get_int32(vid);
        const gchar* name = g_variant_get_string(vname, nullptr);
        /* build the Device here */
        devices.push_back(std::make_shared<Device>(new Device::Impl(id, name)));
      }
      g_variant_unref(sensors);
    }
    else
    {
      std::cerr << "error getting sensors\n";
    }
    g_clear_object(&finder);
  }
  else
  {
    std::cerr << "error getting finder\n";
  }

  return devices;
}


} // namspace Gokan



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
#include "libgokan/dbusinterface.h"


int
main()
{
  GokanFinder* finder = gokan_finder_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,
                                                            G_DBUS_PROXY_FLAGS_NONE,
                                                            "com.canonical.Gokan",
                                                            "/com/canonical/Gokan/Finder",
                                                            nullptr,
                                                            nullptr);
  if (!finder)
  {
    std::cerr << "error getting finder\n";
    return 1;
  }

  GVariant* sensors = nullptr;
  gboolean bstat = gokan_finder_call_sensors_get_by_type_sync(finder,
                                                              "all",
                                                              &sensors,
                                                              nullptr,
                                                              nullptr);
  if (!bstat)
  {
    std::cerr << "error getting sensors\n";
    return 1;
  }

  gsize count = g_variant_n_children(sensors);
  std::cout << count << " sensor devices found\n";
  for (gsize i = 0; i < count; ++i)
  {
    GVariant* variant = g_variant_get_child_value(sensors, i);
    GVariant* vid = g_variant_get_child_value(variant, 0);
    GVariant* vname = g_variant_get_child_value(variant, 1);
    gint id = g_variant_get_int32(vid);
    const gchar* name = g_variant_get_string(vname, nullptr);
    std::cout << " " << id << " " << name << "\n";
  }

  g_variant_unref(sensors);
  g_clear_object(&finder);
}


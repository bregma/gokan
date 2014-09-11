
/**
 * @file gokand/dbusservice.cpp
 * @brief gokand D-Bus service
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
#include "gokand/dbusservice.h"

#include <gio/gio.h>
#include "gokand/configuration.h"
#include "gokand/controller.h"
#include "gokand/sensor.h"
#include "libgokan/dbusinterface.h"


namespace Gokand
{

struct DbusService::Impl
{
  Impl(Configuration* configuration,
       const char*    service_name,
       Controller*    controller)
  : configuration_(configuration)
  , controller_(controller)
  , error_quark_(g_quark_from_static_string("gokan-dbus-impl"))
  , bus_owner_id_(g_bus_own_name(G_BUS_TYPE_SESSION,
                                 service_name,
                                 G_BUS_NAME_OWNER_FLAGS_NONE,
                                 on_bus_acquired,
                                 on_name_acquired,
                                 on_name_lost,
                                 this,
                                 NULL))
  { }


  ~Impl()
  {
    g_bus_unown_name(bus_owner_id_);
  }


  static gboolean
  on_handle_sensors_get_by_type(GokanFinder*           interface,
                                GDBusMethodInvocation* invocation,
                                const gchar*           type_name,
                                gpointer               user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("%s(%s)\n", __PRETTY_FUNCTION__, type_name);
    }

    try
    {
      GVariantBuilder* builder = g_variant_builder_new(G_VARIANT_TYPE("a(is)"));
      for (auto const& sensor: impl->controller_->sensors_get_by_type(type_name))
      {
        g_variant_builder_add(builder, "(is)", sensor->id(), sensor->type().c_str());
      }
      GVariant* matching_sensors = g_variant_new("a(is)", builder);
      g_variant_builder_unref(builder);

      gokan_finder_complete_sensors_get_by_type(interface, invocation, matching_sensors);
    }
    catch (std::exception& ex)
    {
      g_dbus_method_invocation_return_error(invocation,
                                            impl->error_quark_,
                                            0,
                                            "error getting device by type: %s",
                                            ex.what());
    }
    return TRUE;
  }


  static gboolean
  on_handle_sensors_start_watch_by_type(GokanFinder*           interface,
                                        GDBusMethodInvocation* invocation,
                                        const gchar*           type_name,
                                        gpointer               user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("%s(%s)\n", __PRETTY_FUNCTION__, type_name);
    }

    try
    {
      /** @todo implement me */
      gokan_finder_complete_sensors_start_watch_by_type(interface, invocation);
    }
    catch (std::exception& ex)
    {
      g_dbus_method_invocation_return_error(invocation,
                                            impl->error_quark_,
                                            0,
                                            "error starting watch by type: %s",
                                            ex.what());
    }
    return TRUE;
  }


  static gboolean
  on_handle_sensors_stop_watch_by_type(GokanFinder*           interface,
                                       GDBusMethodInvocation* invocation,
                                       const gchar*           type_name,
                                       gpointer               user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("%s(%s)\n", __PRETTY_FUNCTION__, type_name);
    }

    try
    {
      /** @todo implement me */
      gokan_finder_complete_sensors_stop_watch_by_type(interface, invocation);
    }
    catch (std::exception& ex)
    {
      g_dbus_method_invocation_return_error(invocation,
                                            impl->error_quark_,
                                            0,
                                            "error stopping watch by type: %s",
                                            ex.what());
    }
    return TRUE;
  }


  static gboolean
  on_handle_start_read(GokanDevice*           interface,
                       GDBusMethodInvocation* invocation,
                       gint                   sensor_id,
                       gpointer               user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("%s(%d)\n", __PRETTY_FUNCTION__, sensor_id);
    }

    try
    {
      /** @todo implement me */
      gokan_device_complete_start_read(interface, invocation);
    }
    catch (std::exception& ex)
    {
      g_dbus_method_invocation_return_error(invocation,
                                            impl->error_quark_,
                                            0,
                                            "error starting read: %s",
                                            ex.what());
    }
    return TRUE;
  }


  static gboolean
  on_handle_stop_read(GokanDevice*           interface,
                       GDBusMethodInvocation* invocation,
                       gint                   sensor_id,
                       gpointer               user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("%s(%d)\n", __PRETTY_FUNCTION__, sensor_id);
    }

    try
    {
      /** @todo implement me */
      gokan_device_complete_stop_read(interface, invocation);
    }
    catch (std::exception& ex)
    {
      g_dbus_method_invocation_return_error(invocation,
                                            impl->error_quark_,
                                            0,
                                            "error stopping read: %s",
                                            ex.what());
    }
    return TRUE;
  }


  static void
  on_bus_acquired(GDBusConnection* connection,
                  const gchar*,
                  gpointer         user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("acquired the session bus\n");
    }
    GError* error = NULL;
    GokanFinder* finder_interface = gokan_finder_skeleton_new();
    g_signal_connect(finder_interface,
                     "handle-sensors-get-by-type",
                     G_CALLBACK (on_handle_sensors_get_by_type),
                     user_data);
    g_signal_connect(finder_interface,
                     "handle-sensors-start-watch-by-type",
                     G_CALLBACK (on_handle_sensors_start_watch_by_type),
                     user_data);
    g_signal_connect(finder_interface,
                     "handle-sensors-stop-watch-by-type",
                     G_CALLBACK (on_handle_sensors_stop_watch_by_type),
                     user_data);

    gboolean bstat = g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(finder_interface),
                                                      connection,
                                                      "/com/canonical/Gokan/Finder",
                                                      &error);
    if (!bstat)
    {
      g_print("error exporting Finder D-Bus interface: %s", error->message);
      g_error_free(error);
    }

    GokanDevice* device_interface = gokan_device_skeleton_new();
    g_signal_connect(device_interface,
                     "handle-start-read",
                     G_CALLBACK (on_handle_start_read),
                     user_data);
    g_signal_connect(device_interface,
                     "handle-stop-read",
                     G_CALLBACK (on_handle_stop_read),
                     user_data);
    bstat = g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(device_interface),
                                             connection,
                                             "/com/canonical/Gokan/Device",
                                             &error);
    if (!bstat)
    {
      g_print("error exporting Device D-Bus interface: %s", error->message);
      g_error_free(error);
    }
  }


  static void
  on_name_acquired(GDBusConnection*,
                   const gchar*     name,
                   gpointer         user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("acquired the name %s on the session bus\n", name);
    }
  }


  static void
  on_name_lost(GDBusConnection* connection,
               const gchar*     name,
               gpointer         user_data)
  {
    Impl* impl = static_cast<Impl*>(user_data);
    if (!connection)
    {
      g_print("can not connect to the session bus\n");
    }
    if (impl->configuration_->is_verbose_mode())
    {
      g_print("lost the name %s on the session bus\n", name);
    }
  }

public:
  Configuration*  configuration_;
  Controller*     controller_;
  GQuark          error_quark_;
  guint           bus_owner_id_;
};


DbusService::
DbusService(Configuration* configuration,
            Controller*    controller)
: impl_(new DbusService::Impl(configuration, "com.canonical.Gokan", controller))
{ }


DbusService::
~DbusService()
{ }

} // namespace Gokand


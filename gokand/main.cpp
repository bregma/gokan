/**
 * @file gokand/main.cpp
 * @brief gokan service daemon program entry point.
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
#include <glib.h>
#include <glib-unix.h>
#include "gokand/configuration.h"
#include "gokand/controller.h"
#include "gokand/dbusservice.h"
#include <iostream>

using namespace Gokand;


/** C++ wrapper for GMainLoop for exception safety. */
typedef std::unique_ptr<GMainLoop, void(*)(GMainLoop*)>  main_loop_t;


/**
 * Signal handler for INT and TERM signals
 *
 * Shuts the daemon down gracefully.  Required to get valgrind to report useful
 * information.
 */
static gboolean
quit_cb(gpointer loop)
{
  if (loop)
    g_idle_add((GSourceFunc)g_main_loop_quit, loop);
  else
    exit(0);
  return FALSE;
}


int
main(int argc, char* argv[])
{
  try
  {
    Configuration config(argc, argv);
    Controller    controller(&config);
    DbusService   dbus_service(&config, &controller);

    main_loop_t main_loop(g_main_loop_new(NULL, FALSE), g_main_loop_unref);
    g_unix_signal_add(SIGTERM, quit_cb, main_loop.get());
    g_unix_signal_add(SIGINT,  quit_cb, main_loop.get());
    g_main_loop_run(main_loop.get());
  }
  catch (std::exception const& ex)
  {
    std::cerr << "exception caught: " << ex.what() << "\n"
              << "exiting...\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "unknown exception caught, "
              << "exiting...\n";
    return 1;
  }
  return 0;
}

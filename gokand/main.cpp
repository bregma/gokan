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
#include "gokand/configuration.h"
#include <iostream>

using namespace Gokand;


int
main(int argc, char* argv[])
{
  try
  {
    Configuration confg(argc, argv);
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

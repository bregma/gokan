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
#ifndef GOKAND_DBUSSERVICE_H
#define GOKAND_DBUSSERVICE_H 1

#include <memory>


namespace Gokand
{
class Configuration;
class Controller;


/**
 * Provides the D-Bus service for the Gokan daemon.
 */
class DbusService
{
public:
  struct Impl;

public:
  DbusService(Configuration* configuration,
              Controller*    controller);
  ~DbusService();

private:
  std::unique_ptr<Impl> impl_;
};

} // namespace Gokand

#endif /* GOKAND_DBUSSERVICE_H */

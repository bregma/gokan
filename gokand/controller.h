/**
 * @file gokand/controller.h
 * @brief gokand controller interface
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
#ifndef GOKAND_CONTROLLER_H
#define GOKAND_CONTROLLER_H 1

#include <memory>


namespace Gokand
{
class Configuration;

/**
 * A master controller for aggregating the various components of the Gokan
 * service.
 */
class Controller
{
public:
  Controller(Configuration* configuration);
  ~Controller() ;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace Gokand

#endif /* GOKAND_CONTROLLER_H */

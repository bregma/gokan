/**
 * @file gokand/sensorimpl.h
 * @brief A system sensor device back end implementation base class.
 */
/* 
 * Copyright 2014 Canonical Ltd.
 * 
 * Phasia is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISDEVICEIMPL
 * QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GOKAND_SENSORIMPL_H_
#define GOKAND_SENSORIMPL_H_

#include <iosfwd>
#include <memory>
#include <string>


namespace Gokand
{

class SensorImpl
{
public:
  virtual
  ~SensorImpl();

  /** Gets the name of the device. */
  virtual std::string const&
  name() const = 0;

  /** Enables the device for data detection. */
  virtual void
  enable() = 0;

  /** Disables the device for data detection. */
  virtual void
  disable() = 0;

  /** Opens a data connection to the device. */
  virtual int
  open() = 0;

  /** Opens a data connection to the device. */
  virtual void
  close() = 0;

  /** Writes descriptive information about the device to a stream. */
  virtual std::ostream&
  print(std::ostream&) = 0;
};

} // namspace Gokand

#endif /* GOKAND_SENSORIMPL_H */

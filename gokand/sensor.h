/**
 * @file libgokan/sensor.h
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
#ifndef GOKAND_SENSOR_H_
#define GOKAND_SENSOR_H_

#include <memory>
#include <vector>


namespace Gokand
{

/**
 * A base class for sensor back-end implementations.
 */
class SensorImpl;


/**
 * A base class for various sensor devices.
 */
class Sensor
{
public:
  /**
   * Sensors are handled internally by a unique identifier.
   */
  typedef int Id;

  /**
   * Sensor types are represented by strings.  It's just more readable that
   * way.
   */
  typedef std::string Type;

  /**
   * An owning smart pointer to a sensor device.
   */
  typedef std::shared_ptr<Sensor> Ptr;

  /**
   * A collection of sensor devices.
   */
  typedef std::vector<Sensor::Ptr> Bag;

  /**
   * An owning smart pointer to an internal sensor implementation.
   */
  typedef std::unique_ptr<SensorImpl> ImplPtr;

public:
  Sensor(Id id, ImplPtr impl);
  virtual ~Sensor();

  /**
   * Gets the sensor's unique identifier.
   */
  Sensor::Id
  id() const;

  /**
   * Gets the autodetected type of the sensor.
   */
  Sensor::Type
  type() const;

  /**
   * Enables input frmo the sensor device.
   */
  void
  enable();

  /**
   * Disables input frmo the sensor device.
   */
  void
  disable();

  /**
   * Prepares the sensor device for reporting data.
   */
  int
  open();

  /**
   * Stops the reporting of data from te device.
   */
  void
  close();

  friend std::ostream&
  operator<<(std::ostream&, Ptr const&);

private:
  Id      id_;
  ImplPtr impl_;
};


/**
 * Streams Sensor Device internals.
 */
std::ostream&
operator<<(std::ostream&, Sensor::Ptr const&);

/**
 * Handy creation function for sensor devices.
 *
 * @param[in] impl The sensor implementation.  The sensor will take ownership of
 *                 the object.
 */
Sensor::Ptr
create_sensor_with_impl(SensorImpl* impl);

} // namspace Gokand

#endif /* GOKAND_SENSOR_H_*/


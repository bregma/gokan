/**
 * @file test/gtest_gokand_create_sensor.cpp
 * @brief Unit tests of the sensor creation function.
 */

/*
 * Copyright 2013 Canonical Ltd.
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "gokand/sensor.h"
#include "gokand/sensorimpl.h"

using namespace ::Gokand;
using namespace ::testing;


class MockSensorImpl
: public SensorImpl
{
public:
  MOCK_CONST_METHOD0(name, std::string const&());
  MOCK_METHOD0(enable, void());
  MOCK_METHOD0(disable, void());
  MOCK_METHOD0(open, int());
  MOCK_METHOD0(close, void());
  MOCK_METHOD1(print, std::ostream&(std::ostream&));
};


TEST(TestGokandCreateSensor, create_sensor)
{
  Sensor::Ptr sensor1 = create_sensor_with_impl(new MockSensorImpl);
  Sensor::Ptr sensor2 = create_sensor_with_impl(new MockSensorImpl);
  ASSERT_NE(sensor1->id(), sensor2->id());
}


# This file is part of Gokan, a Linux sensor suite
#
# Copyright 2014 Canonical Ltd.
# 
# Gokan is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published by
# the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISFACTORY
# QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
# License for more details.
# 
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.

check_LIBRARIES = libgmock.a
check_PROGRAMS = gtest_gokand
TESTS = $(check_PROGRAMS)

nodist_libgmock_a_SOURCES = \
  $(GMOCK_PREFIX)/src/gmock-all.cc \
  $(GTEST_PREFIX)/src/gtest-all.cc

libgmock_a_CPPFLAGS = \
  -Wno-missing-field-initializers \
  $(GMOCK_CPPFLAGS) \
  $(GTEST_CPPFLAGS)

nodist_gtest_gokand_SOURCES = \
  $(GMOCK_PREFIX)/src/gmock_main.cc

gtest_gokand_SOURCES = \
  gtest_gokand_create_sensor.cpp

gtest_gokand_CPPFLAGS = \
  -I$(top_srcdir) \
  $(GMOCK_CPPFLAGS) \
  $(GTEST_CPPFLAGS)

gtest_gokand_LDADD = \
  $(top_builddir)/gokand/libgokand.a \
  $(top_builddir)/libgokan/libgokan.la \
  libgmock.a \
  -lpthread


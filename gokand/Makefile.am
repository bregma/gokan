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

bin_PROGRAMS = gokand
noinst_LIBRARIES = libgokand.a

gokand_SOURCES = \
  main.cpp

libgokand_a_SOURCES = \
  configuration.h  configuration.cpp \
  controller.h     controller.cpp \
  dbusservice.h    dbusservice.cpp \
  finder.h         finder.cpp \
  sensor.h         sensor.cpp \
  sensorimpl.h     sensorimpl.cpp \
  sensorimpliio.h  sensorimpliio.cpp

libgokand_a_CPPFLAGS = \
  -I$(top_srcdir) \
  $(GIO_CFLAGS)

gokand_CPPFLAGS = \
  -I$(top_srcdir) \
  $(GIO_CFLAGS) \
  $(UDEV_CFLAGS)

gokand_LDADD = \
  $(top_builddir)/gokand/libgokand.a \
  $(top_builddir)/libgokan/libgokan.la \
  $(GIO_LIBS) \
  $(UDEV_LIBS)


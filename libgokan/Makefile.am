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

lib_LTLIBRARIES = libgokan.la

generated_dbus_sources = \
  dbusinterface.h dbusinterface.c

libgokan_la_SOURCES = \
  libgokan_config.h \
  dbusinterface.h          dbusinterface.c \
  device.h                 device.cpp \
  deviceimpl.h             deviceimpl.cpp

libgokan_la_CPPFLAGS = \
  -DLIBLIBGOKAN_BUILDING_DSO=1 \
  -I${top_srcdir} \
  ${UDEV_CFLAGS} \
  ${GIO_CFLAGS}

libgokan_la_LDFLAGS = \
  ${UDEV_LIBS} \
  ${GIO_LIBS}

$(generated_dbus_sources): com.canonical.Gokan.xml
	$(AM_V_GEN)gdbus-codegen --interface-prefix com.canonical. \
                                 --generate-c-code  dbusinterface  $^

BUILT_SOURCES = $(generated_dbus_sources)
CLEANFILES = $(BUILT_SOURCES)
EXTRA_DIST = com.canonical.Gokan.xml


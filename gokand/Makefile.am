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

gokand_SOURCES = \
  configuration.h  configuration.cpp \
  controller.h     controller.cpp \
  dbusservice.h    dbusservice.cpp \
  main.cpp

gokand_CPPFLAGS = \
  -I$(top_srcdir) \
  $(GIO_CFLAGS)

gokand_LDADD = \
  $(top_builddir)/libgokan/libgokan.la \
  $(GIO_LIBS)


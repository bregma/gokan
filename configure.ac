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

AC_PREREQ([2.60])
AC_INIT([Gokan],
        [1.0.0],
        [stephen.webb@canonical.com],
        [gokan])
AC_CONFIG_AUX_DIR([config-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.13 foreign dist-xz])
AM_SILENT_RULES([yes])

AC_PROG_CC_C_O
AC_PROG_CXX

LT_PREREQ([2.2.6b])
LT_INIT

PKG_CHECK_MODULES([GIO],  [gio-unix-2.0])
PKG_CHECK_MODULES([UDEV], [libudev])
CHECK_GTEST

AC_SUBST(AM_CXXFLAGS, "-Wall -Wextra -pedantic -std=c++11")

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libgokan/Makefile])
AC_CONFIG_FILES([gokand/Makefile])
AC_CONFIG_FILES([test/Makefile])
AC_CONFIG_FILES([tools/Makefile])
AC_OUTPUT

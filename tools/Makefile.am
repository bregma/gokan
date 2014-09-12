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

bin_PROGRAMS = \
  gokan-ls

tool_cppflags = \
  -I${top_srcdir}

tool_ldadd = \
  ${top_builddir}/libgokan/libgokan.la

gokan_ls_SOURCES = \
  gokan-ls.cpp

gokan_ls_CPPFLAGS = \
  $(tool_cppflags) \
  $(GIO_CFLAGS)

gokan_ls_LDADD = \
  $(tool_ldadd) \
  $(GIO_LIBS)



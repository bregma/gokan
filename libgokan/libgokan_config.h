/**
 * @file gokan/libgokan_config.h
 * @brief Library configuration definitions.
 */
/* 
 * Copyright 2014 Canonical Ltd.
 * 
 * Phasia is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranties of MERCHANTABILITY, SATISFACTORY
 * QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGOKAN_CONFIG_H_
#define LIBGOKAN_CONFIG_H_

/* Definitions for cross-platform portability, because although this is
 * originally implemented for Linux, there is nothing really in the API that is
 * Linux-specific.
 */
#if __GNUC__ >= 4
# define LIBGOKAN_HELPER_DSO_IMPORT __attribute__((visibility("default")))
# define LIBGOKAN_HELPER_DSO_EXPORT __attribute__((visibility("default")))
#else
# define LIBGOKAN_HELPER_DSO_IMPORT
# define LIBGOKAN_HELPER_DSO_EXPORT
#endif

/* Define symbols as exported or imported, depending on what's getting built. */
#if defined(LIBLIBGOKAN_BUILDING_DSO)
# define LIBGOKAN_EXPORT      LIBGOKAN_HELPER_DSO_EXPORT
#else
# define LIBGOKAN_EXPORT      LIBGOKAN_HELPER_DSO_IMPORT
#endif


#endif /* LIBGOKAN_CONFIG_H_*/

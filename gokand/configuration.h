/**
 * @file gokand/configuration.h
 * @brief gokand configuration wrapper
 */

/*
 * Copyright 2014 Canonical Ltd.
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
#ifndef GOKAND_CONFIGURATION_H
#define GOKAND_CONFIGURATION_H 1

#include <iosfwd>
#include <memory>


namespace Gokand
{

/**
 * Encapsulates the runtime configuration for the gokan service daemon.
 */
class Configuration
{
public:
  Configuration(int argc, char* argv[]);
  ~Configuration();

  /** Indicates if the program is running in verbose mode or not. */
  bool
  is_verbose_mode() const;

  /** Dumps the configuration in himan-readbale form. */
  std::ostream&
  print(std::ostream& ostr) const;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};


/**
 * Handle debugging function.
 */
inline std::ostream&
operator<<(std::ostream& ostr, Configuration const& config)
{ return config.print(ostr); }

} // namespace Gokand

#endif /* GOKAND_CONFIGURATION_H */

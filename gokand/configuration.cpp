/**
 * @file gokand/configuration.cpp
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
#include "gokand/configuration.h"

#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <string.h>


/**
 * The command-line options.
 */
static struct option long_options[] = {
  { "help",     no_argument,       NULL, 'h' },
  { "verbose",  no_argument,       NULL, 'v' },
  { "version",  no_argument,       NULL, 'V' },
  { 0,          no_argument,       NULL,  0  }
};


namespace Gokand
{

struct Configuration::Impl
{
  Impl(int argc, char* argv[]);

  void
  print_help_and_exit();

  void
  print_version(std::ostream& ostr);

  void
  print_version_and_exit();

public:
  bool        is_verbose_mode_;
};


Configuration::Impl::
Impl(int argc, char* argv[])
: is_verbose_mode_(false)
{
  while (1)
  {
    int option_index = 0;
    int c = getopt_long(argc, argv, "hmvV", long_options, &option_index);
    if (c == -1)
      break;

    switch (c)
    {
      case '?':
      case 'h':
        print_help_and_exit();
        break;
      case 'v':
        is_verbose_mode_ = true;
        break;
      case 'V':
        print_version_and_exit();
        break;
      default:
        break;
    }
  }

  if (is_verbose_mode_)
    print_version(std::cout);
}


void Configuration::Impl::
print_help_and_exit()
{
  std::cerr <<
    "usage:\n"
    "  gokand [OPTION...] - service daemon for electronic senses\n"
    "\n"
    "Options:\n"
    "  -h, --help               Print this message and exit.\n"
    "  -v, --verbose            Keep a running commentary on stdout.\n"
    "  -V, --version            Print the program version and exit.\n"
    "\n";
  std::exit(0);
}


void Configuration::Impl::
print_version(std::ostream& ostr)
{
  ostr << PACKAGE_STRING << "\n";
  ostr << "Copyright 2014 Canonical Ltd.\n\n";
}


void Configuration::Impl::
print_version_and_exit()
{
  print_version(std::cout);
  std::exit(0);
}


Configuration::
Configuration(int argc, char* argv[])
: impl_(new Impl(argc, argv))
{
  if (is_verbose_mode())
    std::cout << *this << "\n";
}


Configuration::
~Configuration()
{ }


bool Configuration::
is_verbose_mode() const
{
  return impl_->is_verbose_mode_;
}


std::ostream& Configuration::
print(std::ostream& ostr) const
{
  return ostr << std::boolalpha
    << "Configuration:\n"
    << "  verbose mode:          " << is_verbose_mode() << "\n"
    << std::noboolalpha;
}

} // namespace Gokand


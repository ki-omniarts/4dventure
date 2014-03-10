// {{{ License
/*
 * messages.h
 * This file is part of 4dventure
 *
 * Copyright (C) 2012 - KiNaudiz
 *
 * 4dventure is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * 4dventure is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 4dventure. If not, see <http://www.gnu.org/licenses/>.
 */
// }}} License

// {{{ Include guards
#ifndef ADVENTURE_MESSAGES_HPP
#define ADVENTURE_MESSAGES_HPP
// }}} Include guards

// {{{ Includes
#include <string>
// }}} Includes

// {{{ Message constants
constexpr char MESSAGE_COMMAND_NOT_FOUND[]  = "Command not found.";
constexpr char MESSAGE_HELP[]               =
R"(
      This programm allows you to run specific text adventures
                    written in Lua for 4dventure.
             You can close a game anytime using 'Ctrl-C'.
)";
constexpr char MESSAGE_USAGE[]              =
R"(
Usage:
    %s [Option|Filename]
Options:
    --help      Prints a small programm information
    --license   Print the licensing information
)";
constexpr char MESSAGE_LICENSE[]            =
R"(
            4dventure  Copyright (C) 2012-2014  KiNaudiz

This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
     This is free software, and you are welcome to redistribute it
                    under certain conditions;
)";
// }}} Message constants

// {{{ Include guards
#endif
// }}} Include guards

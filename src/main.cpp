// {{{ License
/*
 * main.cpp
 * This file is part of 4dventure
 *
 * Copyright (C) 2012 - KiNaudiz
 *
 * 4dvnture is free software; you can redistribute it and/or modify
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

// {{{ Includes
#include "loop.hpp"
#include "version.hpp"
#include "messages.hpp"
// }}} Includes

// {{{ main()
int main(int argc,char* argv[])
{
    if ( argc > 1)
    {
        // {{{ With an argument
        if (std::string(argv[1]) == "--help")
            // {{{ Print help
            // print help if the the program is run with --help
            std::cout << MESSAGE_HELP << std::endl;
            // }}} Print help
        else if (std::string(argv[1]) == "--license")
            // {{{ Print license
            // print license if the the program is run with --license
            std::cout << MESSAGE_LICENSE << std::endl;
            // }}} Print license
        else if (std::string(argv[1]) == "--version") {
            // {{{ Print version
            // print license if the the program is run with --license
            std::cout << MESSAGE_LICENSE << std::endl;
            std::cout << version::MAJOR << "." << version::MINOR << "."
                << version::PATCH << "-" << version::SUFFIX << " "
                << version::NAME << std::endl;
            // }}} Print version
        } else
            // run program with given filename or path
            Loop::loop().run(argv[1]);
        // }}} With an argument
    } else {
        // {{{ Usage
        // print a usage message if the program is run w/o args
        std::printf(MESSAGE_USAGE,argv[0]);
        // }}} Usage
    }

    return 0;
}
// }}} main()

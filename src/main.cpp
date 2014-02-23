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

extern "C" 
{
    #include "physfs.h"
}
// }}} Includes

// {{{ main()
int main(int argc,char* argv[])
{
    if ( argc > 1)
    {
        // {{{ With an argument
        if (std::string(argv[1]) == "--help")
        {
            // {{{ Print help
            std::cout << "This programm allows you to run specific "
                << "text adventures written in Lua for 4dventure." 
                << std::endl;
            std::cout << "You can close a game anytime using 'Ctrl-C'."
                << std::endl;
            // }}} Print help
        } else if (std::string(argv[1]) == "--license") {
            // {{{ Print license
            std::cout << "4dventure  Copyright (C) 2012  KiNaudiz"
                << std::endl;
            std::cout << "This program comes with ABSOLUTELY NO WARRANTY; "
                << "for details type `show w'." << std::endl;
            std::cout << "This is free software, and you are welcome to " 
                << "redistribute it under certain conditions;" << std::endl;
            // }}} Print license
        } else if (std::string(argv[1]) == "--version") {
            // {{{ Print version
            std::cout << version::MAJOR << "." << version::MINOR << "."
                << version::PATCH << "-" << version::SUFFIX << " "
                << version::NAME << std::endl;
            // }}} Print version
        } else {
            int zip = 0;
            if (!PHYSFS_init(argv[0]))
                zip=-1;
            Loop::loop().run(argv[1],zip);
            PHYSFS_deinit(); // TODO: RAII-Helper
        }
        // }}} With an argument
    } else {
        // {{{ Usage
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [Option|Filename]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "--help\tPrints a small programm information"
            << std::endl;
        std::cout << "--license\tPrint the licensing information"
            << std::endl;
        // }}} Usage
    }

    return 0;
}
// }}} main()

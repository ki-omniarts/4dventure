/*
 * main.cpp
 * This file is part of <program name>
 *
 * Copyright (C) 2012 - KiNaudiz
 *
 * <program name> is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * <program name> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <program name>. If not, see <http://www.gnu.org/licenses/>.
 */

#include "loop.h"

int main(int argc,char* argv[])
{
    if ( argc > 1)
    {
        if (std::string(argv[1]) == "--help")
        {
            std::cout << "This programm allows you to run specific "
                << "text adventures written in Lua for 4dventure." 
                << std::endl;
            std::cout << "You can close a game anytime using 'quit'."
                << std::endl;
        } else if (std::string(argv[1]) == "--license") {
            std::cout << "4dventure  Copyright (C) 2012  KiNaudiz"
                << std::endl;
            std::cout << "This program comes with ABSOLUTELY NO WARRANTY; "
                << "for details type `show w'." << std::endl;
            std::cout << "This is free software, and you are welcome to " 
                << "redistribute it under certain conditions;"
                << "type `show c' for details." << std::endl;
        } else {
            Loop::loop().run(argv[1]);
        }
    } else {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [Option|Filename]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "--help\tPrints a small programm information"
            << std::endl;
        std::cout << "--license\tPrint the licensing information"
            << std::endl;
    }

    return 0;
}

// {{{ License
/*
 * random.h
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
#ifndef ADVENTURE_RANDOM_HPP
#define ADVENTURE_RANDOM_HPP
// }}} Include guards

// {{{ Includes
#include <random>

#include "lua.hpp"
// }}} Includes

// {{{ random_ranged()
/*! returns a random number between ll and uu to Lua */
inline int random_ranged(lua_State* L)
{
    // check if two arguments are given in Lua
    const int args = lua_gettop(L);
    if (args > 1)
    {
        // check if both arguments are integers
        if (lua_isnumber(L,-args) && lua_isnumber(L,-args+1))
        {
            // fetch operands
            const int ll = lua_tonumber(L,-args);
            const int uu = lua_tonumber(L,-args+1);
        
            // create random number generator
            std::random_device generator;
            std::uniform_int_distribution<int> distribution(ll,uu);
            
            // compute result and push it to Lua stack
            const int result = distribution(generator);
            lua_pushnumber(L,result);
        }
    }
    // number of returned values (1)
    return 1;
}
// }}} random_ranged()

// {{{ Indiclude Guards
#endif
// }}} Indiclude Guards

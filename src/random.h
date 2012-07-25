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

#ifndef ADVENTURE_RANDOM_H
#define ADVENTURE_RANDOM_H

#include <random>

#include "lua.hpp"

inline int random_ranged(lua_State* L)
{
    const int args = lua_gettop(L);
    if (args > 1)
    {
        if (lua_isnumber(L,-args) && lua_isnumber(L,-args+1))
        {
            const int ll = lua_tonumber(L,-args);
            const int uu = lua_tonumber(L,-args+1);
        
            std::random_device generator;
            std::uniform_int_distribution<int> distribution(ll,uu);
            
            const int result = distribution(generator);
            lua_pushnumber(L,result);
        }
    }
    return 1;
}

#endif

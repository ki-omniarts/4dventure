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

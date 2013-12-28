/*
 * loop.cpp
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

#include "loop.hpp"
#include <stdexcept>

Loop& Loop::loop()
{
    static Loop instance;
    return instance;
}

Loop::Loop()
{}

Loop::~Loop() noexcept {}

void Loop::run(const std::string& filename)
{
    // LUA
    luaopen_base(L_.get());
    luaL_openlibs(L_.get());

    lua_register(L_.get(),LUA_QUIT,quit_);
    lua_register(L_.get(),LUA_SETMAP,setMap_);
    lua_register(L_.get(),LUA_SETPP,setPlayerPos_);
    lua_register(L_.get(),LUA_GETPP,getPlayerPos_);
    lua_register(L_.get(),LUA_GONORTH,goNorth_);
    lua_register(L_.get(),LUA_GOSOUTH,goSouth_);
    lua_register(L_.get(),LUA_GOEAST,goEast_);
    lua_register(L_.get(),LUA_GOWEST,goWest_);
    lua_register(L_.get(),LUA_DOINPUT,input_);
    lua_register(L_.get(),LUA_RANDOMRANGED,random_ranged);
    lua_register(L_.get(),LUA_SETINPUTPREFIX,setInputPrefix_);

    if (luaL_dofile(L_.get(),filename.c_str()) == 1)
    {
        std::string tmp{""};
        tmp += " is no valid LUA file.";
        tmp += lua_tostring(L_.get(),-1);

        throw std::runtime_error{tmp};
    }
    
    if (!map_->empty())
        throw std::runtime_error{"Empty Map"};

    if (playerPos_ == Point(0,0))
        playerPos_ = map_->startpoint();

    // actual loop
    while(running_)
    {
        lua_getglobal(L_.get(), LUA_EACHTIME );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            lua_call(L_.get(),0,0);

        input_();
        logic_();
    }
}

void Loop::input_()
{
    std::cout << inputPrefix_;
    std::getline(std::cin,inputString_);
}

void Loop::logic_()
{
    if  ( inputString_ == COMMAND_QUIT )
        running_ = false;
    else
    {     
        lua_getglobal(L_.get(), LUA_INPUT(inputString_).c_str() );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            lua_call(L_.get(),0,0);
        else
        {
            lua_getglobal(L_.get(), LUA_INPUT("").c_str() );
            if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            {
                lua_pushstring(L_.get(),inputString_.c_str());
                lua_call(L_.get(),1,1);
                if (!( lua_isboolean(L_.get(),lua_gettop(L_.get())) )
                    || !(lua_toboolean(L_.get(),lua_gettop(L_.get()))) )
                    std::cout << MESSAGE_COMMAND_NOT_FOUND << std::endl;
            }
        }
    }
}

int Loop::setMap_(lua_State* L)
{
    int args = lua_gettop(L);
    if (args > 0)
        if(lua_isstring(L,-args))
            Loop::loop().map_.reset(new Map(lua_tostring(L,-args)));

    return 0;
}

int Loop::setPlayerPos_(lua_State* L)
{
    int args = lua_gettop(L);
    if (args > 1)
        if (lua_isnumber(L,-args) && lua_isnumber(L,-args+1))
            Loop::loop().playerPos_ = 
                Point(lua_tonumber(L,-args),lua_tonumber(L,-args+1));
    
    return 0;
}

int Loop::getPlayerPos_(lua_State* L)
{
    lua_pushnumber(L,Loop::loop().playerPos_.x());
    lua_pushnumber(L,Loop::loop().playerPos_.y());
    
    return 2;
}

int Loop::tileEvent_(lua_State*)//TODO
{
    lua_getglobal(Loop::loop().L_.get(), LUA_ONTILE);
    
    if (lua_isfunction(Loop::loop().L_.get(),lua_gettop(Loop::loop().L_.get())))
    {
        lua_pushstring(Loop::loop().L_.get(),
            (std::string("")+
            static_cast<char>(
                (Loop::loop().map_->symbol(Loop::loop().playerPos_)))).c_str());
        lua_call(Loop::loop().L_.get(),1,0);
    }
    
    return 0;
}

bool Loop::obstacle_(lua_State* L,char c)
{
    lua_getglobal(L,LUA_OBSTACLE);

    if (lua_isfunction(L,lua_gettop(L)))
    {
        lua_pushstring(L,
            (std::string("")+c).c_str());
        lua_call(L,1,1);
        if ( lua_isboolean(L,lua_gettop(L)) )
            return lua_toboolean(L,lua_gettop(L));
    }

    return false;
}

bool Loop::walk_(direction dir)
{
    Point p{0,0};
    uint currentx = Loop::loop().playerPos_.x();
    uint currenty = Loop::loop().playerPos_.y();

    switch (dir)
    {
        case NORTH:
            p = Point(currentx,currenty-1);
            break;
        case SOUTH:
            p = Point(currentx,currenty+1);
            break;
        case EAST:
            p = Point(currentx+1,currenty);
            break;
        case WEST:
            p = Point(currentx-1,currenty);
            break;
        default:
            break;
    }
    if ( Loop::loop().map_->exists(p) 
        && !( obstacle_(Loop::loop().L_.get(),Loop::loop().map_->symbol(p)) ) )
    {
        Loop::loop().playerPos_ = p;
        tileEvent_(Loop::loop().L_.get());
        return true;
    }
        
    return false;
}

int Loop::goNorth_(lua_State* L)
{
    lua_pushboolean(L,( walk_(NORTH) ));
    return 1;
}

int Loop::goSouth_(lua_State* L)
{
    lua_pushboolean(L,( walk_(SOUTH) ));
    return 1;
}

int Loop::goEast_(lua_State* L)
{
    lua_pushboolean(L,( walk_(EAST) ));
    return 1;
}

int Loop::goWest_(lua_State* L)
{
    lua_pushboolean(L,( walk_(WEST) ));
    return 1;
}

int Loop::input_(lua_State* L)
{
    std::cout   << Loop::loop().inputPrefix_;
    std::string s;
    std::getline(std::cin,s);
    lua_pushstring(L,s.c_str());
    return 1;
}

int Loop::setInputPrefix_(lua_State* L)
{
    int args{lua_gettop(L)};
    if (args > 0)
        if (lua_isstring(L,-args))
            Loop::loop().inputPrefix_ = lua_tostring(L,-args);
    return 0;
}

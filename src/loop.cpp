// {{{ License
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
// }}} License

// {{{ Includes
#include "loop.hpp"
#include "version.hpp"

#include <stdexcept>
#include <sstream>
#include <thread>
#include <chrono>

extern "C"
{
    #include "physfs.h"
}
// }}} Includes

// {{{ Loop::loop()
Loop& Loop::loop()
{
    static Loop instance;
    return instance;
}
// }}} Loop::loop()

// {{{ Loop *ctors
// {{{ Constructor
Loop::Loop()
{}
// }}} Constructor

// {{{ Destructor
Loop::~Loop() noexcept {}
// }}} Destructor
// }}} Loop *ctors

// {{{ Loop::doLuaFile_()
bool Loop::doLuaFile_(const std::string& filename)
{
    return luaL_dofile(L_.get(),filename.c_str());
}
// }}} Loop::doLuaFile_()

// {{{ Loop::doLuaZip_()
bool Loop::doLuaZip_(const std::string& filename,int zip)
{
    if (zip==-1)
    {
        std::string tmp{"Can't initialize PhysicsFS!\n"};
        tmp += PHYSFS_getLastError();
        throw std::runtime_error(tmp);
    }

    if (!PHYSFS_mount(filename.c_str(),"",1))
    {
        std::string tmp{"Can't open archive "};
        tmp += filename;
        tmp += "!\n";
        tmp += PHYSFS_getLastError();
        throw std::runtime_error(tmp);
    }

    std::string lua_filename{""};
    for (auto s:LUA_MAIN_FILE)
        if (PHYSFS_exists(s))
        {
            lua_filename = s;
            break;
        }

    if (lua_filename == "")
        throw std::runtime_error("No main file found!");

    std::shared_ptr<PHYSFS_file> lua_file
        { PHYSFS_openRead(lua_filename.c_str()),PHYSFS_close };
    char* buffer = new char[PHYSFS_fileLength(lua_file.get())];
    if (PHYSFS_read(lua_file.get(),buffer,1,PHYSFS_fileLength(lua_file.get())-1)
            ==-1)
        throw std::runtime_error("Could not read main file!");

    std::string lua_main = buffer;
    delete buffer; // TODO improve this part and make it RAII

    return luaL_dostring(L_.get(),lua_main.c_str());
}
// }}} Loop::doLuaZip_()

// {{{ Loop::run()
void Loop::run(const std::string& filename,int zip)
{
    // {{{ LUA init
    luaopen_base(L_.get());
    luaL_openlibs(L_.get());

    // Register Lua functions
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
    lua_register(L_.get(),LUA_SETCMDNOTFOUND,setCommandNotFound_);
    lua_register(L_.get(),LUA_GETVERSION,getVersion_);
    lua_register(L_.get(),LUA_WAIT,wait_);
    // }}} LUA init

    // {{{ Read LUA file
    {
        if (!zip)
        {
            std::fstream tmp{filename};
            std::string buf{"  "};
            char* cbuf = &*buf.begin();
            tmp.read(cbuf,2);
            for (auto s:LUA_ZIP_MAGIC)
                if (buf==s)
                {
                    zip=1;
                    break;
                }
        }
        // execute Lua file or zip
        if ( (zip)?doLuaZip_(filename,zip):doLuaFile_(filename) )
        {
            std::string tmp{""};
            tmp += filename;
            tmp += " is no valid LUA file.\n";
            tmp += lua_tostring(L_.get(),-1);

            // throw exception on error
            throw std::runtime_error{tmp};
        }
    }
    // }}} Read LUA file

    // {{{ Check map
    if (map_->empty())
        // throw exception on error
        throw std::runtime_error{"Empty Map"};
    // }}} Check map

    // {{{ Set Player Position
    if (playerPos_ == Point(0,0))
        playerPos_ = map_->startpoint();
    // }}} Set Player Position

    // {{{ Actual loop
    while(running_)
    {
        // call each time routine
        lua_getglobal(L_.get(), LUA_EACHTIME );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            lua_call(L_.get(),0,0);

        // call subroutines for input and logic
        input_();
        logic_();
    }
    // }}} Actual loop
}
// }}} Loop::run()

// {{{ Loop::input_()
void Loop::input_()
{
    // print prompt prefix
    std::cout << inputPrefix_;
    // read user input
    std::getline(std::cin,inputString_);
}
// }}} Loop::input_()

// {{{ Loop::logic_()
void Loop::logic_()
{
    // holds split arguments
    std::vector<decltype(inputString_)> argv{};

    // {{{ Split arguments
    {
        decltype(inputString_) buf{};
        std::stringstream ss{inputString_};

        while (ss >> buf) 
            argv.push_back(buf);
    }
    // }}} Split arguments

    // {{{ Check for empty command
    if (argv.empty())
    {
        // call empty input routine if user input is empty
        lua_getglobal(L_.get(), LUA_EMPTY_INPUT );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            lua_call(L_.get(),0,0);
        return;
    }
    // }}} Check for empty command

    lua_getglobal(L_.get(), LUA_INPUT(argv[0]).c_str() );
    if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
    {
        // if there is a lua function that corellates the first word of the
        // user's input, call it with all the given arguments
        for (size_t i = 1; i < argv.size(); ++i) 
            lua_pushstring(L_.get(),argv[i].c_str());
        lua_call(L_.get(),argv.size()-1,0);
    }
    else
    {
        // otherwise call the generic input function
        lua_getglobal(L_.get(), LUA_INPUT("").c_str() );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
        {
            for (size_t i = 0; i < argv.size(); ++i) 
                lua_pushstring(L_.get(),argv[i].c_str());
            lua_call(L_.get(),argv.size(),1);
            if (!( lua_isboolean(L_.get(),lua_gettop(L_.get())) )
                    || !(lua_toboolean(L_.get(),lua_gettop(L_.get()))) )
                // if the generic input function returns false
                // give out an error message
                std::cout << cmdNotFound_ << std::endl;
        }
    }
}
// }}} Loop::logic_()

// {{{ Lua functions
// {{{ Loop::setMap_()
int Loop::setMap_(lua_State* L)
{
    // generate a new map
    int args = lua_gettop(L);
    if (args > 0)
        if(lua_isstring(L,-args))
            Loop::loop().map_.reset(new Map(lua_tostring(L,-args)));

    return 0;
}
// }}} Loop::setMap_()

// {{{ Loop::setPlayerPos_()
int Loop::setPlayerPos_(lua_State* L)
{
    // set the player's position
    int args = lua_gettop(L);
    if (args > 1)
        if (lua_isnumber(L,-args) && lua_isnumber(L,-args+1))
            Loop::loop().playerPos_ = 
                Point(lua_tonumber(L,-args),lua_tonumber(L,-args+1));

    return 0;
}
// }}} Loop::setPlayerPos_()

// {{{ Loop::getPlayerPos_()
int Loop::getPlayerPos_(lua_State* L)
{
    // return the player's position
    lua_pushnumber(L,Loop::loop().playerPos_.x());
    lua_pushnumber(L,Loop::loop().playerPos_.y());

    return 2;
}
// }}} Loop::getPlayerPos_()

// {{{ Loop::tileEvent_()
int Loop::tileEvent_(lua_State*)//TODO
{
    lua_getglobal(Loop::loop().L_.get(), LUA_ONTILE);

    if (lua_isfunction(Loop::loop().L_.get(),lua_gettop(Loop::loop().L_.get())))
    {
        // call the tile event routine
        lua_pushstring(Loop::loop().L_.get(),
                (std::string("")+
                 static_cast<char>(
                     (Loop::loop().map_->symbol(Loop::loop().playerPos_)))).c_str());
        lua_call(Loop::loop().L_.get(),1,0);
    }

    return 0;
}
// }}} Loop::tileEvent_()

// {{{ Loop::obstacle_()
bool Loop::obstacle_(lua_State* L,char c)
{
    lua_getglobal(L,LUA_OBSTACLE);

    if (lua_isfunction(L,lua_gettop(L)))
    {
        // call the obstacle routine
        lua_pushstring(L,
                (std::string("")+c).c_str());
        lua_call(L,1,1);
        if ( lua_isboolean(L,lua_gettop(L)) )
            // return what the obstacle routine returned (true on obstacle)
            return lua_toboolean(L,lua_gettop(L));
    }

    // return false on default (no obstacle)
    return false;
}
// }}} Loop::obstacle_()

// {{{ Movement
// {{{ Loop::walk_()
bool Loop::walk_(direction dir)
{
    Point p{0,0};
    uint currentx = Loop::loop().playerPos_.x();
    uint currenty = Loop::loop().playerPos_.y();

    // modify the teporary saved position by the given direction
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
        // if the new position doesn't hit an obstacle
        // save the new position
        Loop::loop().playerPos_ = p;
        // call the tileEvent routine
        tileEvent_(Loop::loop().L_.get());
        // return true if the position has been modified
        return true;
    }

    // return false if the player's position wasn't modified
    return false;
}
// }}} Loop::walk_()

// {{{ Loop::goNorth_()
int Loop::goNorth_(lua_State* L)
{
    lua_pushboolean(L,( walk_(NORTH) ));
    return 1;
}
// }}} Loop::goNorth_()

// {{{ Loop::goSouth_()
int Loop::goSouth_(lua_State* L)
{
    lua_pushboolean(L,( walk_(SOUTH) ));
    return 1;
}
// }}} Loop::goSouth_()

// {{{ Loop::goEast_()
int Loop::goEast_(lua_State* L)
{
    lua_pushboolean(L,( walk_(EAST) ));
    return 1;
}
// }}} Loop::goEast_()

// {{{ Loop::goWest_()
int Loop::goWest_(lua_State* L)
{
    lua_pushboolean(L,( walk_(WEST) ));
    return 1;
}
// }}} Loop::goWest_()
// }}} Movement

// {{{ Loop::input_()
int Loop::input_(lua_State* L)
{
    // print the prompt prefix
    std::cout   << Loop::loop().inputPrefix_;
    std::string s;
    // read the user's input
    std::getline(std::cin,s);
    // return the user's input
    lua_pushstring(L,s.c_str()); // TODO: split_arguments function for Lua
    return 1;
}
// }}} Loop::input_()

// {{{ Loop::setInputPrefix_()
int Loop::setInputPrefix_(lua_State* L)
{
    // set a new prompt prefix
    int args{lua_gettop(L)};
    if (args > 0)
        if (lua_isstring(L,-args))
            Loop::loop().inputPrefix_ = lua_tostring(L,-args);
    return 0;
}
// }}} Loop::setInputPrefix_()

// {{{ Loop::setInputPrefix_()
int Loop::setCommandNotFound_(lua_State* L)
{
    // set a new "command not found" message
    int args{lua_gettop(L)};
    if (args > 0)
        if (lua_isstring(L,-args))
            Loop::loop().cmdNotFound_ = lua_tostring(L,-args);
    return 0;
}
// }}} Loop::setInputPrefix_()

// {{{ Loop::getVersion_()
int Loop::getVersion_(lua_State* L)
{
    // return the version of 4dventure
    lua_pushnumber(L,version::MAJOR);
    lua_pushnumber(L,version::MINOR);
    lua_pushnumber(L,version::PATCH);
    lua_pushstring(L,version::SUFFIX);
    lua_pushstring(L,version::NAME);
    return 5;
}
// }}} Loop::getVersion_()

// {{{ Loop::wait_()
int Loop::wait_(lua_State* L)
{
    int args{lua_gettop(L)};
    if (args > 0)
        if (lua_isnumber(L,-args))
            // sleep for a given number of ms
            std::this_thread::sleep_for(
                    std::chrono::milliseconds(lua_tointeger(L,-args)));
    return 0;
}
// }}} Loop::wait_()
// }}} Lua functions

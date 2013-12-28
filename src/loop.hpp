/*
 * loop.h
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

#ifndef ADVENTURE_LOOP_HPP
#define ADVENTURE_LOOP_HPP

#include "map.hpp"
#include "commands.hpp"
#include "messages.hpp"
#include "lua_vars.hpp"
#include "random.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <fstream>

#include "lua.hpp"

const char INPUT_PREFIX[] = "\t> ";

class Loop
{
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>{new Map{}};
    std::string inputString_    = "";
    bool running_               = true;
    Point playerPos_            = Point{0,0};
    std::string inputPrefix_    = INPUT_PREFIX;

    // LUA
    std::shared_ptr<lua_State>L_= 
        std::shared_ptr<lua_State>{lua_open(),lua_close};
    static int setMap_(lua_State* L);
    static int setPlayerPos_(lua_State* L);
    static int getPlayerPos_(lua_State* L);
    static int goNorth_(lua_State* L);
    static int goSouth_(lua_State* L);
    static int goWest_(lua_State* L);
    static int goEast_(lua_State* L);
    static int quit_(lua_State*) { Loop::loop().running_ = false; return 0; }
    static int tileEvent_(lua_State* L);
    static bool obstacle_(lua_State* L,char c);
    static int input_(lua_State* L);
    static int setInputPrefix_(lua_State* L);

    enum direction { NORTH,EAST,SOUTH,WEST };
    static bool walk_( direction dir );

    Loop(const Loop&)               = delete;
    Loop(Loop&&)                    = delete;
    Loop& operator=(const Loop&)    = delete;
    Loop& operator=(Loop&&)         = delete;

    void input_();
    void logic_();

    Loop();

    public:
        virtual ~Loop() noexcept;
        
        static Loop& loop();

        // FUNCTIONS
        void run(const std::string& filename); // throws std::runtime_error

};

#endif
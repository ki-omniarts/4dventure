// {{{ License
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
// }}} License

// {{{ Include Guards
#ifndef ADVENTURE_LOOP_HPP
#define ADVENTURE_LOOP_HPP
// }}} Include Guards

// {{{ Includes
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
// }}} Includes

// {{{ Constants
/*! Constant holding the default prompt prefix */
constexpr char INPUT_PREFIX[] = "\t> ";
// }}} Constants

// {{{ class Loop
/*! Singleton Loop class holding a global instance of a 4dventure instance */
class Loop
{
    // {{{ Member variables
    /*!< game map */
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>{new Map{}};
    /*!< user input */
    std::string inputString_    = "";
    /*!< "command not found" message in use */
    std::string cmdNotFound_    = MESSAGE_COMMAND_NOT_FOUND;
    /*!< bool controlling continuation */
    bool running_               = true;
    /*!< the player's position on the game map */
    Point playerPos_            = Point{0,0};
    /*!< prompt prefix in use */
    std::string inputPrefix_    = INPUT_PREFIX;

    /*!< Lua instance */
    std::shared_ptr<lua_State>L_= 
        std::shared_ptr<lua_State>{luaL_newstate(),lua_close};
    // }}} Member variables

    // {{{ LUA functions
    /*!< function to set a new map in Lua */
    static int setMap_(lua_State* L);
    /*!< function to set the player's position in Lua */
    static int setPlayerPos_(lua_State* L);
    /*!< function returning the player's position in Lua */
    static int getPlayerPos_(lua_State* L);
    /*!< function to move player northwards in Lua */
    static int goNorth_(lua_State* L);
    /*!< function to move player southwards in Lua */
    static int goSouth_(lua_State* L);
    /*!< function to move player westwards in Lua */
    static int goWest_(lua_State* L);
    /*!< function to move player eastwards in Lua */
    static int goEast_(lua_State* L);
    /*!< function to quit 4dventure from Lua */
    static int quit_(lua_State*) { Loop::loop().running_ = false; return 0; }
    /*!< function crontrolling specific events on map tiles from Lua */
    static int tileEvent_(lua_State* L);
    /*!< function to handle obstacles on map in Lua */
    static bool obstacle_(lua_State* L,char c);
    /*!< function to enforce an input from Lua */
    static int input_(lua_State* L);
    /*!< function to set an input prefix in Lua */
    static int setInputPrefix_(lua_State* L);
    /*!< function to set a "command not found" message in Lua */
    static int setCommandNotFound_(lua_State* L);
    /*!< function returning the 4dventure version to Lua */
    static int getVersion_(lua_State* L);
    /*!< function that holds 4dventure for a specific amount of time in Lua */
    static int wait_(lua_State* L);
    // }}} LUA functions

    // {{{ Movement
    /*!> enum with directions */
    enum direction { NORTH,EAST,SOUTH,WEST };
    /*!> a function to move the player in a specific direction */
    static bool walk_( direction dir );
    // }}} Movement

    // {{{ Deleted operators for Singleton pattern
    Loop(const Loop&)               = delete;
    Loop(Loop&&)                    = delete;
    Loop& operator=(const Loop&)    = delete;
    Loop& operator=(Loop&&)         = delete;
    // }}} Deleted operators for Singleton pattern

    // {{{ Private member functions
    /*!< input phase */
    void input_();
    /*!< logic phase */
    void logic_();
    // }}} Private member functions

    // {{{ private Constructor
    /*!< private constructor method */
    Loop();
    // }}} private Constructor

    public:
        // {{{ Destructor
        /*!< destructor method */
        virtual ~Loop() noexcept;
        // }}} Destructor

        // {{{ Singleton Getter
        /*!< public instance getter */
        static Loop& loop();
        // }}} Singleton Getter

        // {{{ Public member functions
        /*!< public method to run a file */
        void run(const std::string& filename); // throws std::runtime_error
        // }}} Public member functions

};
// }}} class Loop

// {{{ Include Guards
#endif
// }}} Include Guards

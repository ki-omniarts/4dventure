// {{{ License
/*
 * lua_vars.h
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
#ifndef ADVENTUE_LUA_VARS_HPP
#define ADVENTUE_LUA_VARS_HPP
// }}} Include guards

// {{{ Includes
#include <string>
// }}} Includes

// {{{ Lua functions names
// {{{ Callable in LUA
/*! constant for the variable name of the quit function */
constexpr char LUA_QUIT[]           = "adv_quit";
/*! constant for the variable name of the function returning 4dventure's
 * version */
constexpr char LUA_GETVERSION[]     = "adv_version";
/*! constant for the variable name of the function that sets the map */
constexpr char LUA_SETMAP[]         = "adv_setMap";
/*! constant for the variable name of the function that sets the player's
 * position */
constexpr char LUA_SETPP[]          = "adv_setPlayerPosition";
/*! constant for the variable name of the function returning the player's
 * position */
constexpr char LUA_GETPP[]          = "adv_getPlayerPosition";
/*! constatnt for the variable name of the function to go north */
constexpr char LUA_GONORTH[]        = "adv_goNorth";
/*! constatnt for the variable name of the function to go south */
constexpr char LUA_GOSOUTH[]        = "adv_goSouth";
/*! constatnt for the variable name of the function to go east */
constexpr char LUA_GOEAST[]         = "adv_goEast";
/*! constatnt for the variable name of the function to go west */
constexpr char LUA_GOWEST[]         = "adv_goWest";
/*! constatnt for the variable name of the function to enforce a user input */
constexpr char LUA_DOINPUT[]        = "adv_input";
/*! constatnt for the variable name of the function returning a random number */
constexpr char LUA_RANDOMRANGED[]   = "adv_random_ranged";
/*! constatnt for the variable name of the function to set the prompt prefix */
constexpr char LUA_SETINPUTPREFIX[] = "adv_setInputPrefix";
/*! constatnt for the variable name of the function to set the "command not
 * found" message */
constexpr char LUA_SETCMDNOTFOUND[] = "adv_setCommandNotFound";
/*! constatnt for the variable name of the function to halt 4dventure for
 * a while */
constexpr char LUA_WAIT[]           = "adv_wait";
/*! constant for the variable name of the function to handle an empty input */
constexpr char LUA_EMPTY_INPUT[]    = "adv_emptyInput";

/*! inline function to handle the variable names of functions that handle user
 * input */
inline std::string LUA_INPUT(const std::string& s)
{ return std::string("adv_input_")+s; }
// }}} Callable in LUA

// {{{ Called by 4dventure
/*! constant for the variable name of the function to handle tile events */
constexpr char LUA_ONTILE[]         = "adv_onTile";
/*! constant for the variable name of the function to handle obstacles on map */
constexpr char LUA_OBSTACLE[]       = "adv_obstacle";
/*! constant for the variable name of the function that is run on each loop */
constexpr char LUA_EACHTIME[]       = "adv_eachTime";
// }}} Called by 4dventure
// }}} Lua functions names

// {{{ Include guards
#endif
// }}} Include guards

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
constexpr char LUA_QUIT[]           = "adv_quit";
constexpr char LUA_GETVERSION[]     = "adv_version";
constexpr char LUA_SETMAP[]         = "adv_setMap";
constexpr char LUA_SETPP[]          = "adv_setPlayerPosition";
constexpr char LUA_GETPP[]          = "adv_getPlayerPosition";
constexpr char LUA_GONORTH[]        = "adv_goNorth";
constexpr char LUA_GOSOUTH[]        = "adv_goSouth";
constexpr char LUA_GOEAST[]         = "adv_goEast";
constexpr char LUA_GOWEST[]         = "adv_goWest";
constexpr char LUA_DOINPUT[]        = "adv_input";
constexpr char LUA_RANDOMRANGED[]   = "adv_random_ranged";
constexpr char LUA_SETINPUTPREFIX[] = "adv_setInputPrefix";
constexpr char LUA_SETCMDNOTFOUND[] = "adv_setCommandNotFound";
constexpr char LUA_EMPTY_INPUT[]    = "adv_emptyInput";

inline std::string LUA_INPUT(const std::string& s)
{ return std::string("adv_input_")+s; }
// }}} Callable in LUA

// {{{ Called by 4dventure
constexpr char LUA_ONTILE[]         = "adv_onTile";
constexpr char LUA_OBSTACLE[]       = "adv_obstacle";
constexpr char LUA_EACHTIME[]       = "adv_eachTime";
// }}} Called by 4dventure
// }}} Lua functions names

// {{{ Include guards
#endif
// }}} Include guards

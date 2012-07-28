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

#ifndef ADVENTUE_LUA_VARS_H
#define ADVENTUE_LUA_VARS_H

#include <string>

const char LUA_QUIT[]           = "adv_quit";
const char LUA_SETMAP[]         = "adv_setMap";
const char LUA_SETPP[]          = "adv_setPlayerPosition";
const char LUA_GETPP[]          = "adv_getPlayerPosition";
const char LUA_GONORTH[]        = "adv_goNorth";
const char LUA_GOSOUTH[]        = "adv_goSouth";
const char LUA_GOEAST[]         = "adv_goEast";
const char LUA_GOWEST[]         = "adv_goWest";
const char LUA_DOINPUT[]        = "adv_input";
const char LUA_RANDOMRANGED[]   = "adv_random_ranged";
const char LUA_SETINPUTPREFIX[] = "adv_setInputPrefix";

inline std::string LUA_INPUT(const std::string s)
{ return std::string("adv_input_")+s; }

const char LUA_ONTILE[]         = "adv_onTile";
const char LUA_OBSTACLE[]       = "adv_obstacle";
const char LUA_EACHTIME[]       = "adv_eachTime";

#endif

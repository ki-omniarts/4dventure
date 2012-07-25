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

inline std::string LUA_INPUT(const std::string s)
{ return std::string("adv_input_")+s; }

const char LUA_ONTILE[]         = "adv_onTile";
#endif

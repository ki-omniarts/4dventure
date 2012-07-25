#ifndef ADVENTURE_LOOP_H
#define ADVENTURE_LOOP_H

#include "map.h"
#include "commands.h"
#include "messages.h"
#include "lua_vars.h"
#include "random.h"

#include <memory>
#include <iostream>
#include <string>
#include <fstream>

#include "lua.hpp"

const char INPUT_PREFIX[] = "\t> ";

class Loop
{
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>(new Map());
    std::string inputString_    = "";
    bool running_               = true;
    Point playerPos_            = Point(0,0);

    // LUA
    std::shared_ptr<lua_State>L_= 
        std::shared_ptr<lua_State>(lua_open(),lua_close);
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
        virtual ~Loop();
        
        static Loop& loop();

        // FUNCTIONS
        void run(const std::string& filename);

};

#endif

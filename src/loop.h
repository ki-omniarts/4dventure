#ifndef ADVENTURE_LOOP_H
#define ADVENTURE_LOOP_H

#include "map.h"
#include "commands.h"
#include "messages.h"
#include "lua_vars.h"

#include <memory>
#include <iostream>
#include <string>
#include <fstream>

#include "lua.hpp"

class Loop
{
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>(new Map());
    std::string inputString_    = "";
    std::string outputString_   = "";
    bool running_               = true;

    // LUA
    std::shared_ptr<lua_State>L_= 
        std::shared_ptr<lua_State>(lua_open(),lua_close);
    static int setMap_(lua_State* L);
    static int quit_(lua_State*) { Loop::loop().running_ = false; return 0; }

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

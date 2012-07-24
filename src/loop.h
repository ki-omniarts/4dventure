#ifndef ADVENTURE_LOOP_H
#define ADVENTURE_LOOP_H

#include "map.h"
#include "commands.h"
#include "messages.h"

#include <memory>
#include <iostream>
#include <string>
#include <fstream>

class Loop
{
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>(new Map());
    std::string inputString_    = "";
    std::string outputString_   = "";
    bool running_               = true;

    Loop(const Loop&)               = delete;
    Loop(Loop&&)                    = delete;
    Loop& operator=(const Loop&)    = delete;
    Loop& operator=(Loop&&)         = delete;

    void input_();
    void logic_();

    public:
        // CONSTRUCTOR
        Loop();
        virtual ~Loop();
        
        // FUNCTIONS
        void run();

};

#endif

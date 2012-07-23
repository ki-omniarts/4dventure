#include "point.h"
#include "commands.h"
#include "messages.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>

class Loop
{
    typedef std::vector<std::vector<Point>> Map;
    std::unique_ptr<Map> map_   = std::unique_ptr<Map>(new Map);
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

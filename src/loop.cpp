#include "loop.h"

Loop::Loop()
{
    std::fstream mapfile("test.map",std::ios::in);
    std::string mapstring;

    while(!mapfile.eof())
        mapfile >> mapstring;
    mapfile.close();

    map_ = std::unique_ptr<Map>(new Map(mapstring));
    // map_ = std::unique_ptr<Map>(new Map("S"));
}

Loop::~Loop() {}

void Loop::run()
{
    while(running_)
    {
        input_();
        logic_();
    }
}

void Loop::input_()
{
    std::cout << "> ";
    std::cin >> inputString_;
}

void Loop::logic_()
{
    if ( inputString_ == COMMAND_QUIT )
        running_ = false;
    else
        std::cout << MESSAGE_COMMAND_NOT_FOUND << std::endl;
}

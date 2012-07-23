#include "loop.h"

Loop::Loop() {}
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

#include "loop.h"

Loop& Loop::loop()
{
    static Loop instance;
    return instance;
}

Loop::Loop()
{}

Loop::~Loop() {}

void Loop::run(const std::string& filename)
{
    // LUA
    luaopen_base(L_.get());
    luaL_openlibs(L_.get());

    lua_register(L_.get(),LUA_QUIT,quit_);
    lua_register(L_.get(),LUA_SETMAP,setMap_);

    luaL_dofile(L_.get(),filename.c_str()); 
    
    // actual loop
    while(running_)
    {
        input_();
        logic_();
    }
}

void Loop::input_()
{
    std::cout << "\t> ";
    std::cin >> inputString_;
}

void Loop::logic_()
{
    if ( inputString_ == COMMAND_QUIT )
        running_ = false;
    else
        std::cout << MESSAGE_COMMAND_NOT_FOUND << std::endl;
}

int Loop::setMap_(lua_State* L)
{
    int args = lua_gettop(L);
    if (args > 0)
    {
        if(lua_isstring(L,-args))
        {
            Loop::loop().map_.reset(new Map(lua_tostring(L,-args)));
        }
    }

    return 0;
}


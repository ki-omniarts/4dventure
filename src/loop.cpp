#include "loop.h"

Loop::Loop()
{
    // LUA
    luaopen_base(L_.get());
    luaL_openlibs(L_.get());
    luaL_dofile(L_.get(),"test.lua"); 
    
    map_ = std::unique_ptr<Map>(new Map(getMap(L_.get())));
}

std::string Loop::getMap(lua_State* L)
{
    lua_getglobal(L, LUA_MAP);

    if(lua_isstring(L,lua_gettop(L)))
        return lua_tostring(L,-1);
    std::cout << "not found" << std::endl;
    return "";
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

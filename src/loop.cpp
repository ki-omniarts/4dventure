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
    lua_register(L_.get(),LUA_SETPP,setPlayerPos_);
    lua_register(L_.get(),LUA_GETPP,getPlayerPos_);
    lua_register(L_.get(),LUA_GONORTH,goNorth_);
    lua_register(L_.get(),LUA_GOSOUTH,goSouth_);
    lua_register(L_.get(),LUA_GOEAST,goEast_);
    lua_register(L_.get(),LUA_GOWEST,goWest_);

    luaL_dofile(L_.get(),filename.c_str()); 
    
    if (!map_->valid())
        std::cerr << "No valid Map specified." << std::endl;

    if (playerPos_ == Point(0,0))
        playerPos_ = map_->startpoint();

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
    if  ( inputString_ == COMMAND_QUIT )
        running_ = false;
    else
    {     
        lua_getglobal(L_.get(), LUA_INPUT(inputString_).c_str() );
        if (lua_isfunction(L_.get(),lua_gettop(L_.get())))
            lua_call(L_.get(),0,0);
        else
            std::cout << MESSAGE_COMMAND_NOT_FOUND << std::endl;
    }
}

int Loop::setMap_(lua_State* L)
{
    int args = lua_gettop(L);
    if (args > 0)
        if(lua_isstring(L,-args))
            Loop::loop().map_.reset(new Map(lua_tostring(L,-args)));

    return 0;
}

int Loop::setPlayerPos_(lua_State* L)
{
    int args = lua_gettop(L);
    if (args > 1)
        if (lua_isnumber(L,-args) && lua_isnumber(L,-args+1))
            Loop::loop().playerPos_ = 
                Point(lua_tonumber(L,-args),lua_tonumber(L,-args+1));
    
    return 0;
}

int Loop::getPlayerPos_(lua_State* L)
{
    lua_pushnumber(L,Loop::loop().playerPos_.x());
    lua_pushnumber(L,Loop::loop().playerPos_.y());
    
    return 0;
}

int Loop::tileEvent_(lua_State*)
{
    lua_getglobal(Loop::loop().L_.get(), LUA_ONTILE);
    
    if (lua_isfunction(Loop::loop().L_.get(),lua_gettop(Loop::loop().L_.get())))
    {
        lua_pushstring(Loop::loop().L_.get(),
            (std::string("")+
            (Loop::loop().map_->symbol(Loop::loop().playerPos_))).c_str());
        lua_call(Loop::loop().L_.get(),1,0);
    }
    
    return 0;
}

int Loop::goNorth_(lua_State* L)
{
    if ( Loop::loop().map_->exists
        (Point(Loop::loop().playerPos_.x(),Loop::loop().playerPos_.y()-1) ) )
    {
        lua_pushboolean(L,true);
        Loop::loop().playerPos_ =
            Point(Loop::loop().playerPos_.x(),Loop::loop().playerPos_.y()-1);
    } else {
        lua_pushboolean(L,false);
    }
    return 0;
}

int Loop::goSouth_(lua_State* L)
{
    if ( Loop::loop().map_->exists
        (Point(Loop::loop().playerPos_.x(),Loop::loop().playerPos_.y()+1) ) )
    {
        lua_pushboolean(L,true);
        Loop::loop().playerPos_ =
            Point(Loop::loop().playerPos_.x(),Loop::loop().playerPos_.y()+1);
    } else {
        lua_pushboolean(L,false);
    }
    return 0;
}

int Loop::goEast_(lua_State* L)
{
    if ( Loop::loop().map_->exists
        (Point(Loop::loop().playerPos_.x()+1,Loop::loop().playerPos_.y()) ) )
    {
        lua_pushboolean(L,true);
        Loop::loop().playerPos_ =
            Point(Loop::loop().playerPos_.x()+1,Loop::loop().playerPos_.y());
    } else {
        lua_pushboolean(L,false);
    }
    return 0;
}

int Loop::goWest_(lua_State* L)
{
    if ( Loop::loop().map_->exists
        (Point(Loop::loop().playerPos_.x()-1,Loop::loop().playerPos_.y()-1) ) )
    {
        lua_pushboolean(L,true);
        Loop::loop().playerPos_ =
            Point(Loop::loop().playerPos_.x()-1,Loop::loop().playerPos_.y()-1);
    } else {
        lua_pushboolean(L,false);
    }
    return 0;
}

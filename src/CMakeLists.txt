CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# about the project
#------------------
project( 4dventure )
SET( 4DVENTURE_VERSION_MAJOR "0" )
SET( 4DVENTURE_VERSION_MINOR "1" )
SET( 4DVENTURE_VERSION_PATCH "0" )

# Paths
#------
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Requirements
#-------------
include(FindLua50)
include(FindLua51)
include(FindLua52)

if ( ( NOT ${LUA51_FOUND} ) AND ( NOT ${LUA50_FOUND} 
        AND ( NOT ${LUA52_FOUND} ) ) )
    message ( FATAL_ERROR "Lua not found!" )
endif ( ( NOT ${LUA51_FOUND} ) AND ( NOT ${LUA50_FOUND} 
        AND ( NOT ${LUA52_FOUND} ) ) )

include_directories(
    ${LUA_INCLUDE_DIR}
)

#Files
#-----
SET (4dventureSRC
    ${CMAKE_CURRENT_SOURCE_DIR}/loop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/map.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Flags
#------
set(CMAKE_CXX_FLAGS "-Wall -g -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Compile
#--------
add_executable( ${PROJECT_NAME}
    ${4dventureSRC}
)

target_link_libraries( ${PROJECT_NAME}
    ${LUA_LIBRARIES}
)

# Install
#--------
install (PROGRAMS ${CMAKE_BINARY_DIR}/${PROJECT_NAME} DESTINATION bin)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# {{{ about the project
#------------------
project( 4dventure )
SET( 4DVENTURE_VERSION_MAJOR "1" )
SET( 4DVENTURE_VERSION_MINOR "2" )
SET( 4DVENTURE_VERSION_PATCH "0" )
SET( 4DVENTURE_VERSION_SUFFIX "" )
SET( 4Dventure_VERSION_NAME "Chuck the Plant" )

include(GNUInstallDirs)

SET( LIBRARY_NAME c4dventure )
# }}} about the project

# {{{ Paths
#------
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# {{{ Lua
set( LUA_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/lua
)

set( LUA_SRC
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c
    ${LUA_DIR}/lbitlib.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/linit.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c
    ${LUA_DIR}/lstrlib.c
    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
)
# }}} Lua
# }}} Paths

# {{{ Additional variables
SET ( PLATTFORM
    "none"
)

OPTION( STANDALONE
    "Set this to build a standalone version with lua built in."
    off
)

OPTION( LIBRARY
    "Set this to build a shared or static library depending on BUILD_SHARED_LIBS."
    on
)
# }}} Additional variables

# {{{ Requirements
#-------------
if( NOT ${STANDALONE} )
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
else( NOT ${STANDALONE} )
    
endif( NOT ${STANDALONE} )
# }}} Requirements

# {{{ Files
#-----
SET (4dventureLibSRC
    ${CMAKE_CURRENT_SOURCE_DIR}/loop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/map.cpp
)
SET (4dventureSRC
    ${4dventureLibSRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
if( ${STANDALONE} )
    SET( 4dventureSRC
        ${4dventureSRC}
        ${LUA_SRC}
    )
endif( ${STANDALONE} )

CONFIGURE_FILE (
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp
)
# }}} Files

# {{{ Flags
#------
set(CMAKE_CXX_FLAGS "-Wall -g -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# }}} Flags

# {{{ Compile
#--------
add_executable( ${PROJECT_NAME}
    ${4dventureSRC}
)
if ( ${LIBRARY} )
    add_library( ${LIBRARY_NAME}
        ${4dventureLibSRC} )
endif ( ${LIBRARY} )

if( NOT ${STANDALONE} )
target_link_libraries( ${PROJECT_NAME}
    ${LUA_LIBRARIES}
)
if ( ${LIBRARY} )
    target_link_libraries( ${LIBRARY_NAME}
        ${LUA_LIBRARIES}
    )
endif ( ${LIBRARY} )
endif( NOT ${STANDALONE} )
# }}} Compile

# {{{ Install
#--------
install (PROGRAMS ${CMAKE_BINARY_DIR}/${PROJECT_NAME} DESTINATION bin)
if( ${LIBRARY} )
    install(DIRECTORY src/ DESTINATION include/4dventure
        FILES_MATCHING PATTERN "*.h")
    if( ${BUILD_SHARED_LIBS} )
        install(TARGETS ${LIBRARY_NAME} LIBRARY DESTINATION
            ${CMAKE_INSTALL_LIBDIR})
    endif( ${BUILD_SHARED_LIBS} )
endif( ${LIBRARY} )
# }}} Install

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# {{{ about the project
#------------------
project( 4dventure )
SET( 4DVENTURE_VERSION_MAJOR "1" )
SET( 4DVENTURE_VERSION_MINOR "2" )
SET( 4DVENTURE_VERSION_PATCH "2" )
# SET( 4DVENTURE_VERSION_SUFFIX "" )
SET( 4DVENTURE_VERSION_SUFFIX "physicsfs" )
SET( 4DVENTURE_VERSION_NAME "Chuck the Plant" )

include(GNUInstallDirs)

SET( LIBRARY_NAME c4dventure )
# }}} about the project

# {{{ Paths
#------
set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# }}} Paths

# {{{ Additional variables
SET ( PLATTFORM
    "none"
)

OPTION( LIBRARY
    "Set this to build a shared or static library depending on BUILD_SHARED_LIBS."
    on
)
# }}} Additional variables

# {{{ Requirements
#-------------
Find_Path(PhysFS_INCLUDE_DIR physfs.h
    # PATH_SUFFIXES include
    # PATHS
    # /usr/include
    # /usr/local/include
    )
Find_Library( PhysFS_LIBRARY
    NAMES physfs physicsfs
    PATH_SUFFIXES lib lib64 lib32
    PATHS
    /usr
    /
    /usr/local
    )
if ( PhysFS_LIBRARY AND PhysFS_INCLUDE_DIR )
    MESSAGE( STATUS "Found PhysicsFS: ${PhysFS_LIBRARY}" )
else ( PhysFS_LIBRARY AND PhysFS_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "PhysicsFS not found!" )
endif ( PhysFS_LIBRARY AND PhysFS_INCLUDE_DIR )


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

CONFIGURE_FILE (
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp.in
    ${CMAKE_CURRENT_SOURCE_DIR}/version.hpp
)
# }}} Files

# {{{ Flags
#------
set(CMAKE_CXX_FLAGS "-Wall -g -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
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

target_link_libraries( ${PROJECT_NAME}
    ${LUA_LIBRARIES}
    ${PhysFS_LIBRARY}
)
if ( ${LIBRARY} )
    target_link_libraries( ${LIBRARY_NAME}
        ${LUA_LIBRARIES}
        ${PhysFS_LIBRARY}
    )
endif ( ${LIBRARY} )
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

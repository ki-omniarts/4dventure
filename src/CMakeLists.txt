# about the project
#------------------
project( 4dventure )
SET( 4DVENTURE_VERSION_MAJOR "0" )
SET( 4DVENTURE_VERSION_MINOR "1" )
SET( 4DVENTURE_VERSION_PATCH "0" )

# Paths
#------

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

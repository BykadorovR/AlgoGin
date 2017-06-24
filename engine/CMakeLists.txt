cmake_minimum_required(VERSION 3.1)
project(engine)

#include algo headers
include_directories(algo/include)
FILE(GLOB_RECURSE ALGO_HEADERS "algo/*.h*")
source_group("Algo\\include" FILES ${ALGO_HEADERS})

#include graphic headers
include_directories(graphic/include)
FILE(GLOB_RECURSE GRAPHIC_HEADERS "graphic/*.h*")
source_group("Graphic\\include" FILES ${GRAPHIC_HEADERS})

#include algo source
FILE(GLOB_RECURSE ALGO_SOURCE "algo/*.c*")
source_group("Algo\\source" FILES ${ALGO_SOURCE})

#include graphic source
FILE(GLOB_RECURSE GRAPHIC_SOURCE "graphic/*.c*")
source_group("Graphic\\source" FILES ${GRAPHIC_SOURCE})

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_library(${PROJECT_NAME} ${ALGO_SOURCE} ${ALGO_HEADERS} ${GRAPHIC_SOURCE} ${GRAPHIC_HEADERS})
cmake_minimum_required(VERSION 3.1)
project(engine)

#include algo headers
include_directories(algo/include)
FILE(GLOB_RECURSE ALGO_HEADERS "algo/*.h*")
source_group("algo\\include" FILES ${ALGO_HEADERS})

#include algo source
FILE(GLOB_RECURSE ALGO_SOURCE "algo/src/*.c*")
source_group("algo\\src" FILES ${ALGO_SOURCE})

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#need for mismatch resolving
STRING(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

add_library(${PROJECT_NAME} ${ALGO_SOURCE} ${ALGO_HEADERS})
target_link_libraries(${PROJECT_NAME})
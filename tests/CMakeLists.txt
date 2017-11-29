cmake_minimum_required(VERSION 3.7)
project(engine_tests)

ADD_SUBDIRECTORY ("../dependencies/googletest" googletest)
enable_testing()

#include test source
FILE(GLOB_RECURSE TEST_SOURCE "src/*.c*")
source_group("Test\\src" FILES ${TEST_SOURCE})

#include algo headers
include_directories(../engine/algo/include)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

#need for mismatch resolving
STRING(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${TEST_SOURCE})
#set as startup project in VS
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
#paths to library are diferent on win and linux
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build/Release)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build)
endif()

target_link_libraries(${PROJECT_NAME} gtest gtest_main ${ENGINE_LIBRARY})
add_test( ${PROJECT_NAME} ${PROJECT_NAME})
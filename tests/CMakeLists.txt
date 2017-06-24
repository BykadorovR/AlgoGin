cmake_minimum_required(VERSION 3.7)
project(engine_tests)

ADD_SUBDIRECTORY ("../dependencies/googletest" googletest)
enable_testing()

#include test source
FILE(GLOB_RECURSE TEST_SOURCE "src/*.c*")
source_group("Test\\src" FILES ${TEST_SOURCE})

#include algo headers
include_directories(../Engine/algo/include)

#include graphic headers
include_directories(../Engine/graphic/include)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

#need for mismatch resolving
STRING(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${TEST_SOURCE})
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
find_library(ENGINE_LIBRARY engine HINTS ../engine/_build/Release ../engine/_build/Debug)
target_link_libraries(${PROJECT_NAME} gtest gtest_main ${ENGINE_LIBRARY})
add_test( ${PROJECT_NAME} ${PROJECT_NAME})
cmake_minimum_required(VERSION 3.7)
project(engine_app)

#include app source
FILE(GLOB_RECURSE APP_SOURCE "src/*.c*")
source_group("App\\src" FILES ${APP_SOURCE})

#include app headers
include_directories(include)
FILE(GLOB_RECURSE APP_HEADERS "include/*.h*")
source_group("App\\include" FILES ${APP_HEADERS})

#include algo headers
include_directories(../engine/algo/include)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_executable(${PROJECT_NAME} ${APP_HEADERS} ${APP_SOURCE})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

#paths to library are diferent on win and linux
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build/Release)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build)
endif()
target_link_libraries(${PROJECT_NAME} ${ENGINE_LIBRARY})
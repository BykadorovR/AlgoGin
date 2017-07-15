cmake_minimum_required(VERSION 3.7)
project(engine_app)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found. Need to specify path to freeglut folder and to dynamic/static libraries!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
if (NOT GLEW_FOUND)
    message(ERROR " GLEW not found. Need to specify path to glew folder and to dynamic/static libraries!") 
endif()

#########################################################
# FIND DevIL
#########################################################
find_package(DEVIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})
link_libraries(${IL_LIBRARIES})
if (NOT IL_FOUND)
    message(ERROR " IL not found. Need to specify path to il folder and to dynamic/static libraries!") 
endif()

#include app source
FILE(GLOB_RECURSE APP_SOURCE "src/*.c*")
source_group("App\\src" FILES ${APP_SOURCE})

#include app headers
include_directories(include)
FILE(GLOB_RECURSE APP_HEADERS "include/*.h*")
source_group("App\\include" FILES ${APP_HEADERS})

#include algo headers
include_directories(../engine/algo/include)

#include graphic headers
include_directories(../engine/graphic/include)

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
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build/Release ../engine/_build/Debug ../engine/build/Release ../engine/build/Debug)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    find_library(ENGINE_LIBRARY engine HINTS ../engine/_build ../engine/build)
endif()
target_link_libraries(${PROJECT_NAME} ${ENGINE_LIBRARY} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
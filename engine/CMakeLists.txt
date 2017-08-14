cmake_minimum_required(VERSION 3.1)
project(engine)

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
find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})
link_libraries(${IL_LIBRARIES})
if (NOT IL_FOUND)
    message(ERROR " IL not found. Need to specify path to il folder and to dynamic/static libraries!") 
endif()

#include algo headers
include_directories(algo/include)
FILE(GLOB_RECURSE ALGO_HEADERS "algo/*.h*")
source_group("algo\\include" FILES ${ALGO_HEADERS})

#include graphic headers
include_directories(graphic/include)
FILE(GLOB_RECURSE GRAPHIC_HEADERS "graphic/*.h*")
source_group("graphic\\include" FILES ${GRAPHIC_HEADERS})

#include algo source
FILE(GLOB_RECURSE ALGO_SOURCE "algo/*.c*")
source_group("algo\\src" FILES ${ALGO_SOURCE})

#include graphic source
FILE(GLOB_RECURSE GRAPHIC_SOURCE "graphic/*.c*")
source_group("graphic\\src" FILES ${GRAPHIC_SOURCE})

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_library(${PROJECT_NAME} ${ALGO_SOURCE} ${ALGO_HEADERS} ${GRAPHIC_SOURCE} ${GRAPHIC_HEADERS} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
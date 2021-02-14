cmake_minimum_required(VERSION 3.19)

set (CMAKE_CXX_STANDARD 20)
if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
endif()
#need for mismatch resolving
string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(
  googletest
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/googletest
  DOWNLOAD_COMMAND "" # Disable download step
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/googletest
  INSTALL_COMMAND ""
  )

#include algo headers
include_directories(engine/include)
FILE(GLOB_RECURSE ALGO_HEADERS "engine/include/*.h*")
source_group("include" FILES ${ALGO_HEADERS})

#include algo source
FILE(GLOB_RECURSE ALGO_SOURCE "engine/src/*.c*")
source_group("src" FILES ${ALGO_SOURCE})

add_library(engine ${ALGO_SOURCE} ${ALGO_HEADERS})

ADD_SUBDIRECTORY ("dependencies/googletest" googletest)
enable_testing()

include_directories(engine/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#source files
file(GLOB_RECURSE TEST_SOURCE "tests/src/*.c*")
source_group("src" FILES ${TEST_SOURCE})

add_executable(tests ${TEST_SOURCE})
add_dependencies(tests googletest)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/googletest/include)

target_link_libraries(tests PRIVATE engine)

if (WIN32)
	target_link_libraries(tests PRIVATE debug ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/Debug/gtestd.lib)
	target_link_libraries(tests PRIVATE debug ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/Debug/gtest_maind.lib)
	target_link_libraries(tests PRIVATE optimized ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/Release/gtest.lib)
	target_link_libraries(tests PRIVATE optimized ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/Release/gtest_main.lib)
else()
	target_link_libraries(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/libgtest.a)
	target_link_libraries(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/googletest-prefix/src/googletest-build/libgtest_main.a)
	target_link_libraries(tests PRIVATE pthread)
endif()

add_test( tests tests )

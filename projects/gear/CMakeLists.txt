cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)

#set(TARGET_NAME gear)
#include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

#add_subdirectory("tests")

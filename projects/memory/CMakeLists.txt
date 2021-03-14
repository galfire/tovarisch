cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/gear/include)
include_directories(include/tov)

add_subdirectory("tests")

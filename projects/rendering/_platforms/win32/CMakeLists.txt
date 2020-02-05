cmake_minimum_required (VERSION 3.8)

project(rendering_win32)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_win32 STATIC ${SOURCES})

target_link_libraries(rendering_win32 memory)
target_link_libraries(rendering_win32 math)
target_link_libraries(rendering_win32 rendering)

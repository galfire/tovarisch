cmake_minimum_required (VERSION 3.8)

project(rendering_win32_gl)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/win32/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_win32_gl STATIC ${SOURCES})

set(TARGET_NAME rendering_win32_gl)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

target_link_libraries(rendering_win32_gl math)
target_link_libraries(rendering_win32_gl rendering)
target_link_libraries(rendering_win32_gl rendering_win32)
target_link_libraries(rendering_win32_gl rendering_gl)

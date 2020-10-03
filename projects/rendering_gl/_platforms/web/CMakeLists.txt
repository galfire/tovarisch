cmake_minimum_required (VERSION 3.8)

project(rendering_web_gl)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/web/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)
include_directories(include/tov)

message("EMSDK LOCATION: " $ENV{EMSDK})
SET(EMSDK_INCLUDE $ENV{EMSDK}/upstream/emscripten/system/include)
message("EMSDK INCLUDE: " ${EMSDK_INCLUDE})
include_directories(${EMSDK_INCLUDE})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_web_gl STATIC ${SOURCES})

set(TARGET_NAME rendering_web_gl)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

target_link_libraries(rendering_web_gl memory)
target_link_libraries(rendering_web_gl math)
target_link_libraries(rendering_web_gl rendering)
target_link_libraries(rendering_web_gl rendering_web)
target_link_libraries(rendering_web_gl rendering_gl)

cmake_minimum_required (VERSION 3.8)

project(rendering)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/gear/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(include/tov)

include_directories(${SIMDE_DIR})
include_directories(${STB_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering STATIC ${SOURCES})

set(TARGET_NAME rendering)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

target_link_libraries(rendering math)

if(${COMPILER} EQUAL ${COMPILER_EMCC})
    message("Rendering: Adding platform web")
    add_subdirectory(_platforms/web)
else()
    message("Rendering: Adding platform win32")
    add_subdirectory(_platforms/win32)
endif()

add_subdirectory("tests")

# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(player)

set(CMAKE_CXX_STANDARD 20)

include_directories(${SIMDE_DIR})
include_directories(${STB_DIR})

message("CMAKE SOURCE DIR:" ${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/gear/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/web/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/_platforms/web/include)
include_directories($ENV{EMSDK}/upstream/emscripten/system/include)

include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl)

include_directories(${CMAKE_SOURCE_DIR}/application)

#set(CMAKE_AR "em++")
#set(CMAKE_STATIC_LIBRARY_SUFFIX ".bc")
#set(CMAKE_C_CREATE_STATIC_LIBRARY "<CMAKE_AR> -o <TARGET> <LINK_FLAGS> <OBJECTS>")
#set(CMAKE_CXX_CREATE_STATIC_LIBRARY "<CMAKE_AR> -o <TARGET> <LINK_FLAGS> <OBJECTS>")


# Add source to this project's executable.
add_executable (player "player.cpp" "player.h")
set(CMAKE_EXECUTABLE_SUFFIX ".js")


target_link_libraries(player math)
target_link_libraries(player rendering)
target_link_libraries(player rendering_gl)
target_link_libraries(player rendering_web)
target_link_libraries(player rendering_web_gl)

set_target_properties(player
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/player/public"
)

set_target_properties(player
    PROPERTIES
    LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/player/shaders@/shaders --preload-file ${CMAKE_SOURCE_DIR}/player/assets@/assets -s WASM=1 -s USE_WEBGL2=1 -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s TOTAL_MEMORY=128MB -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\""
)

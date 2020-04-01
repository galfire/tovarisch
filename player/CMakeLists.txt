# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(player)

set(CMAKE_CXX_STANDARD 20)

include_directories(${SIMDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/web/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/_platforms/web/include)
include_directories($ENV{EMSDK}/upstream/emscripten/system/include)

include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl)

# Add source to this project's executable.
add_executable (player "player.cpp" "player.h")
set(CMAKE_EXECUTABLE_SUFFIX ".js")

target_link_libraries(player memory)
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
	LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/player/shaders@/shaders -s WASM=1 -s USE_WEBGL2=1 -s USE_GLFW=3 -s OFFSCREENCANVAS_SUPPORT=1 -s TOTAL_MEMORY=64MB -s BINARYEN_METHOD='native-wasm' -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\"]'"
)

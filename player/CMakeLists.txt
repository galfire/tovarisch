# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(player)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)

# Add source to this project's executable.
add_executable (player "player.cpp" "player.h")
set(CMAKE_EXECUTABLE_SUFFIX ".js")

target_link_libraries(player memory)

set_target_properties(player
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/player/public"
)

set_target_properties(player
	PROPERTIES
	LINK_FLAGS "-s WASM=1 -s USE_WEBGL2=1 -s OFFSCREENCANVAS_SUPPORT=1 -s TOTAL_MEMORY=32MB -s BINARYEN_METHOD='native-wasm' -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\"]'"
)

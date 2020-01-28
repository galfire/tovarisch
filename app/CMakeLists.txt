# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)

file(GLOB SOURCES src/*.cpp)

# Add source to this project's executable.
add_executable (app ${SOURCES})

target_link_libraries(app memory)
target_link_libraries(app math)

# TODO: Add tests and install targets if needed.

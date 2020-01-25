# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(render_system_gl)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
else()
	find_package(OpenGL REQUIRED COMPONENTS OpenGL)
endif()

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include/tov)
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)

file(GLOB SOURCES src/*.cpp)
add_library (render_system_gl ${SOURCES})

target_link_libraries(render_system_gl ${OPENGL_LIBRARIES})

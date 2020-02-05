# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(rendering_gl)

set(CMAKE_CXX_STANDARD 20)

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include/tov)
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_gl STATIC ${SOURCES})

target_link_libraries(rendering_gl rendering)

if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
	find_package(glfw3 REQUIRED)
	target_link_libraries(rendering_gl glfw3)
else()
	find_package(OpenGL REQUIRED COMPONENTS OpenGL)
	target_link_libraries(rendering_gl ${OPENGL_LIBRARIES})
endif()

if(WIN32)
	#include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/win32/include)

	add_subdirectory(_platforms/win32)
else()
endif()

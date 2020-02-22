# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(rendering_gl)

set(CMAKE_CXX_STANDARD 20)

set(COMPILER_MSVC 0)
set(COMPILER_GCC 1)
set(COMPILER_EMCC 2)

set(GL_IMPL_GL 0)
set(GL_IMPL_GLES 1)

if(WIN32)
	set(COMPILER ${COMPILER_MSVC})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(COMPILER ${COMPILER_GCC})
elseif(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
	set(COMPILER ${COMPILER_EMCC})
endif()

if(${COMPILER} EQUAL ${COMPILER_MSVC})
	set(GL_IMPL ${GL_IMPL_GL})
elseif(COMPILER EQUAL ${COMPILER_GCC})
	set(GL_IMPL ${GL_IMPL_GLES})
elseif(COMPILER EQUAL ${COMPILER_EMCC})
	set(GL_IMPL ${GL_IMPL_GLES})
endif()

message("COMPILER: " ${COMPILER})
message("GL IMPL: " ${GL_IMPL})

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include/tov)
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)

include_directories(${SIMDE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_gl STATIC ${SOURCES})

target_link_libraries(rendering_gl memory)
target_link_libraries(rendering_gl rendering)

if(${GL_IMPL} EQUAL ${GL_IMPL_GL})
	target_compile_definitions(rendering_gl PUBLIC TOV_GL)
	
	find_package(OpenGL REQUIRED COMPONENTS OpenGL)
	target_link_libraries(rendering_gl ${OPENGL_LIBRARIES})

	include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl)
	if(${COMPILER} EQUAL ${COMPILER_MSVC})
		add_library(glew STATIC IMPORTED)
		set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/projects/rendering_gl/lib/Win32/glew32s.lib)
		target_link_libraries(rendering_gl glew)
	endif()
elseif(${GL_IMPL} EQUAL ${GL_IMPL_GLES})
	target_compile_definitions(rendering_gl PUBLIC TOV_GLES)
	
	find_library(glfw3 REQUIRED)
	target_link_libraries(rendering_gl glfw)
endif()

if(${COMPILER} EQUAL ${COMPILER_MSVC})
	add_subdirectory(_platforms/win32)
elseif(${COMPILER} EQUAL ${COMPILER_EMCC})
	add_subdirectory(_platforms/web)
endif()

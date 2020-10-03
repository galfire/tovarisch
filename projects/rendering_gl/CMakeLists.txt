# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(rendering_gl)

set(CMAKE_CXX_STANDARD 20)

set(GL_IMPL_GL 0)
set(GL_IMPL_GLES 1)
set(GL_IMPL_UNKNOWN 2)

if(${PLATFORM} EQUAL ${PLATFORM_WIN32})
    set(GL_IMPL ${GL_IMPL_GL})
elseif(${PLATFORM} EQUAL ${PLATFORM_WEB})
    set(GL_IMPL ${GL_IMPL_GLES})
else()
    set(GL_IMPL ${GL_IMPL_UNKNOWN})
endif()

message("GL IMPL: " ${GL_IMPL})

include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include/tov)
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)

include_directories(${SIMDE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering_gl STATIC ${SOURCES})

set(TARGET_NAME rendering_gl)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

target_link_libraries(rendering_gl memory)
target_link_libraries(rendering_gl rendering)

if(${GL_IMPL} EQUAL ${GL_IMPL_GL})
    target_compile_definitions(rendering_gl PUBLIC TOV_GL)

    if(${PLATFORM} EQUAL ${PLATFORM_WIN32})
        message("Using OpenGL on WIN32. Including files at ${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl")
        include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl)
        
        target_compile_definitions(rendering_gl PUBLIC GLEW_STATIC)
        
        add_library(glew STATIC IMPORTED)
        set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/projects/rendering_gl/lib/Win32/glew32s.lib)
        target_link_libraries(rendering_gl glew)

        add_library(glfw STATIC IMPORTED)
        set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/projects/rendering_gl/lib/Win32/glfw3.lib)
        target_link_libraries(rendering_gl glfw)
    else()
        message("Platform is not compatible with OpenGL!")
    endif()
elseif(${GL_IMPL} EQUAL ${GL_IMPL_GLES})
    target_compile_definitions(rendering_gl PUBLIC TOV_GLES)
endif()

if(${DEBUG})
    message("Debug mode is on.")
    target_compile_definitions(rendering_gl PUBLIC DEBUG)
else()
    message("Release mode is on.")
endif()

if(${PLATFORM} EQUAL ${PLATFORM_WIN32})
    add_subdirectory(_platforms/win32)
elseif(${PLATFORM} EQUAL ${PLATFORM_WEB})
    add_subdirectory(_platforms/web)
endif()

# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp)

# Add source to this project's executable.
add_executable (app ${SOURCES})
set_target_properties(app PROPERTIES SUFFIX ".exe")

include_directories(${SIMDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/gl)

set(TARGET_NAME app)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

add_custom_command(TARGET app POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/app/shaders/ $<TARGET_FILE_DIR:app>/shaders)

add_custom_command(TARGET app POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/app/assets/ $<TARGET_FILE_DIR:app>/assets)


if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/win32/include)
    include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/_platforms/win32/include)

    # GLEW
    add_library(glew STATIC IMPORTED)
    set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/vendor/Win32/glew32s.lib)
    target_link_libraries(app glew)
endif()

target_link_libraries(app math)
target_link_libraries(app rendering)
target_link_libraries(app rendering_gl)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(app rendering_win32)
    target_link_libraries(app rendering_win32_gl)
endif()

# TODO: Add tests and install targets if needed.

# CMakeList.txt : CMake project for player, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${SIMDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/include)

if(WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/_platforms/win32/include)
	include_directories(${CMAKE_SOURCE_DIR}/projects/rendering_gl/_platforms/win32/include)
else()
endif()

file(GLOB SOURCES src/*.cpp)

# Add source to this project's executable.
add_executable (app ${SOURCES})

target_link_libraries(app memory)
target_link_libraries(app math)
target_link_libraries(app rendering)
target_link_libraries(app rendering_gl)

if(WIN32)
	target_link_libraries(app rendering_win32)
	target_link_libraries(app rendering_win32_gl)
else()
endif()

# TODO: Add tests and install targets if needed.

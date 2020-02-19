cmake_minimum_required (VERSION 3.8)

project(rendering)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(include/tov)

include_directories(${SIMDE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering STATIC ${SOURCES})

target_link_libraries(rendering memory)
target_link_libraries(rendering math)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

if(WIN32)
	add_subdirectory(_platforms/win32)
else()
	add_subdirectory(_platforms/web)
endif()

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(rendering_tests ${TEST_SOURCES})

include_directories(${CATCH_DIR}/single_include)

include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
target_link_libraries(rendering_tests rendering)

enable_testing()
add_test(NAME rendering COMMAND rendering_tests)

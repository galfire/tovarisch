cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(memory STATIC ${SOURCES})

if(${COMPILER} EQUAL ${COMPILER_MSVC})
	# TESTS
	file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
	add_executable(memory_tests ${TEST_SOURCES})

	include_directories(${CATCH_DIR}/single_include)

	include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
	target_link_libraries(memory_tests memory)

	enable_testing()
	add_test(NAME memory_tests COMMAND memory_tests)
endif()

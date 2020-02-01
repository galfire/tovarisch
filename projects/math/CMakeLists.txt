cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(include/tov)

message(${SIMDE_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(math STATIC ${SOURCES})

include_directories(${SIMDE_DIR})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(math_tests ${TEST_SOURCES})

include_directories(${CATCH_DIR}/single_include)

include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
target_link_libraries(math_tests math)

enable_testing()
add_test(NAME math_tests COMMAND math_tests)

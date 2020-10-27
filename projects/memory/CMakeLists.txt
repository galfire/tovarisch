cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(memory STATIC ${SOURCES})

set(TARGET_NAME memory)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(memory_tests ${TEST_SOURCES})
set_target_properties(memory_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME memory_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${CATCH_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
target_link_libraries(memory_tests memory)

enable_testing()
add_test(NAME memory_tests COMMAND memory_tests)

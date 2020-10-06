cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(include/tov)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(math STATIC ${SOURCES})

include_directories(${SIMDE_DIR})

set(TARGET_NAME math)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(math_tests ${TEST_SOURCES})
set_target_properties(math_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME math_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${CATCH_DIR}/single_include)

include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
target_link_libraries(math_tests math)

enable_testing()
add_test(NAME math_tests COMMAND math_tests)

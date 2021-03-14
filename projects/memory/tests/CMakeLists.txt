file(GLOB_RECURSE TEST_SOURCES *.cpp)
add_executable(memory_tests ${TEST_SOURCES})
set_target_properties(memory_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME memory_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${DOCTEST_DIR}/doctest)
include_directories(${TROMPLOEIL_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)

enable_testing()
add_test(NAME memory_tests COMMAND memory_tests)

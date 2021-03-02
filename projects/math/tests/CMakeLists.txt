file(GLOB_RECURSE TEST_SOURCES *.cpp)
add_executable(math_tests ${TEST_SOURCES})
set_target_properties(math_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME math_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${DOCTEST_DIR}/doctest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)

target_link_libraries(math_tests math)

enable_testing()
add_test(NAME math_tests COMMAND math_tests)

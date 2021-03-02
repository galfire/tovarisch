file(GLOB_RECURSE TEST_SOURCES *.cpp)
add_executable(rendering_tests ${TEST_SOURCES})
set_target_properties(rendering_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME rendering_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${DOCTEST_DIR}/doctest)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)

target_link_libraries(rendering_tests rendering)

enable_testing()
add_test(NAME rendering COMMAND rendering_tests)

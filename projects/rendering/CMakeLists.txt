cmake_minimum_required (VERSION 3.8)

project(rendering)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/projects/core/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/math/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/memory/include)
include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
include_directories(include/tov)

include_directories(${SIMDE_DIR})
include_directories(${STB_DIR})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(rendering STATIC ${SOURCES} "include/tov/rendering/pipeline/framebuffer.h" "include/tov/rendering/producers/gbuffer_producer.h" "tests/producers/dependency_node_tests.cpp" "include/tov/rendering/producers/skybox_producer.h")

set(TARGET_NAME rendering)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

target_link_libraries(rendering math)
target_link_libraries(rendering memory)

if(${COMPILER} EQUAL ${COMPILER_EMCC})
    message("Rendering: Adding platform web")
    add_subdirectory(_platforms/web)
else()
    message("Rendering: Adding platform win32")
    add_subdirectory(_platforms/win32)
endif()

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
add_executable(rendering_tests ${TEST_SOURCES})
set_target_properties(rendering_tests PROPERTIES SUFFIX ".exe")

set(TARGET_NAME rendering_tests)
include(${CMAKE_SOURCE_DIR}/projects/cmake/debug.cmake)

include_directories(${CATCH_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/projects/rendering/include)
target_link_libraries(rendering_tests rendering)

enable_testing()
add_test(NAME rendering COMMAND rendering_tests)

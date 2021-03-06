﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_SYSTEM_NAME Generic)

project ("tovarisch")

###
# SIMDe

configure_file(vendor/external/simde.cmake simde/download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/simde/download)
if(result)
  message(FATAL_ERROR "CMake step for SIMDe failed: ${result}")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/simde/download)
if(result)
  message(FATAL_ERROR "CMake step for SIMDe failed: ${result}")
endif()

set(SIMDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/simde/src/)

###
# stb

configure_file(vendor/external/stb.cmake stb/download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stb/download)
if(result)
  message(FATAL_ERROR "CMake step for stb failed: ${result}")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/stb/download)
if(result)
  message(FATAL_ERROR "CMake step for stb failed: ${result}")
endif()

set(STB_DIR ${CMAKE_CURRENT_BINARY_DIR}/stb/src/)

### 
# doctest

configure_file(vendor/external/doctest.cmake doctest/download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doctest/download)
if(result)
  message(FATAL_ERROR "CMake step for doctest failed: ${result}")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doctest/download)
if(result)
  message(FATAL_ERROR "CMake step for doctest failed: ${result}")
endif()

set(DOCTEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/doctest/src/)

### 
# tromploeil

configure_file(vendor/external/tromploeil.cmake tromploeil/download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tromploeil/download)
if(result)
  message(FATAL_ERROR "CMake step for tromploeil failed: ${result}")
endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tromploeil/download)
if(result)
  message(FATAL_ERROR "CMake step for tromploeil failed: ${result}")
endif()

set(TROMPLOEIL_DIR ${CMAKE_CURRENT_BINARY_DIR}/tromploeil/src/)


# Include sub-projects.

include(${CMAKE_SOURCE_DIR}/projects/cmake/compiler.cmake)
include(${CMAKE_SOURCE_DIR}/projects/cmake/platform.cmake)

if(${COMPILER} EQUAL ${COMPILER_MSVC})
    add_compile_options("/EHsc")
endif()

add_subdirectory("projects/gear")
add_subdirectory("projects/memory")
add_subdirectory("projects/math")
add_subdirectory("projects/rendering")
add_subdirectory("projects/rendering_gl")

add_subdirectory (${EXECUTABLE_SUBDIRECTORY})

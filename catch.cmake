cmake_minimum_required (VERSION 3.8)

project(catch NONE)

include(ExternalProject)
ExternalProject_Add(catch
  GIT_REPOSITORY    https://github.com/catchorg/Catch2.git
  GIT_TAG           devel
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/catch/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/catch/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

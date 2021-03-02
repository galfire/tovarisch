cmake_minimum_required (VERSION 3.8)

project(doctest NONE)

include(ExternalProject)
ExternalProject_Add(doctest
  GIT_REPOSITORY    https://github.com/onqtam/doctest.git
  GIT_TAG           2.4.5
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/doctest/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/doctest/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

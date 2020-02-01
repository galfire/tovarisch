cmake_minimum_required (VERSION 3.8)

project(simde NONE)

include(ExternalProject)
ExternalProject_Add(simde
  GIT_REPOSITORY    https://github.com/nemequ/simde.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/simde/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/simde/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

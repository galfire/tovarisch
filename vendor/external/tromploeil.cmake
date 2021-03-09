cmake_minimum_required (VERSION 3.8)

project(trompeloeil NONE)

include(ExternalProject)
ExternalProject_Add(trompeloeil
  GIT_REPOSITORY    https://github.com/rollbear/trompeloeil.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/tromploeil/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/tromploeil/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

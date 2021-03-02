cmake_minimum_required (VERSION 3.8)

project(stb NONE)

include(ExternalProject)
ExternalProject_Add(stb
  GIT_REPOSITORY    https://github.com/nothings/stb.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/stb/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/stb/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

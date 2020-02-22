cmake_minimum_required (VERSION 3.8)

project(glew NONE)

include(ExternalProject)
ExternalProject_Add(glew
  GIT_REPOSITORY    https://github.com/nigels-com/glew.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/glew/src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/glew/build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

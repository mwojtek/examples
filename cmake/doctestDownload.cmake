cmake_minimum_required(VERSION 3.0)
project(doctestDownload NONE)

include(ExternalProject)

ExternalProject_Add( doctest
   GIT_REPOSITORY    https://github.com/onqtam/doctest.git
   GIT_TAG           master
   SOURCE_DIR        ${CMAKE_BINARY_DIR}/doctest/src
   BINARY_DIR        ${CMAKE_BINARY_DIR}/doctest/build
   CONFIGURE_COMMAND ""
   BUILD_COMMAND     ""
   INSTALL_COMMAND   "")

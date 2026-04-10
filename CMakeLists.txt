cmake_minimum_required(VERSION 3.25)

set(RAN_VER_MAJ 0)
set(RAN_VER_MIN 0)
set(RAN_VER_REV 1)

set(RAN_VER "${RAN_VER_MAJ}.${RAN_VER_MIN}.${RAN_VER_REV}")

project(ranmath VERSION ${RAN_VER} LANGUAGES CXX)

file(GLOB_RECURSE RAN_HEADERS
  LIST_DIRECTORIES FALSE
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/ranmath*.hpp
)

add_library(ranmath INTERFACE)
add_Library(ranmath::ranmath ALIAS ranmath)
target_include_directories(ranmath
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
set_target_properties(ranmath PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20)

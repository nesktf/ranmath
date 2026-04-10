cmake_minimum_required(VERSION 3.25)

set(RAN_VER_MAJ 0)
set(RAN_VER_MIN 0)
set(RAN_VER_REV 1)

set(RAN_VER "${RAN_VER_MAJ}.${RAN_VER_MIN}.${RAN_VER_REV}")

project(ranmath VERSION ${RAN_VER} LANGUAGES CXX)

option(RAN_TESTS "Build tests" OFF)
option(RAN_SINGLE "Generate single header file" OFF)

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
set_target_properties(ranmath PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 20
  EXPORT_NAME ranmath::ranmath
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if (RAN_TESTS)
  add_subdirectory(test)
endif()

if (RAN_SINGLE)
  find_package(Python3 REQUIRED)

  file(GLOB RAN_SINGLE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.*)

  add_custom_command(
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath"
    COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/script/single.py" --input "${CMAKE_CURRENT_SOURCE_DIR}/include" --output "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath/ran.hpp"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/script/single.py" "${RAN_SINGLE_SRC}"
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath/ran.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath/forward.hpp"
  )
  add_custom_target(ranmath_single_header_generator ALL
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/script/single.py"
    "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath/ran.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/ranmath/forward.hpp"
    "${RAN_SINGLE_SRC}"
  )

  add_Library(ranmath_single INTERFACE)
  add_library(ranmath::ranmath::single ALIAS ranmath_single)
  set_target_properties(ranmath_single PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 20
    EXPORT_NAME ranmath::ranmath::single
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/include"
  )
endif()

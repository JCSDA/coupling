# (C) Copyright 2021-2021 UCAR
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

cmake_minimum_required( VERSION 3.12 )

project( coupling VERSION 1.0.0 LANGUAGES CXX )

## Ecbuild integration
find_package( ecbuild 3.3.2 REQUIRED )
include( ecbuild_system NO_POLICY_SCOPE )
ecbuild_declare_project()
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )
set( CMAKE_DIRECTORY_LABELS coupling )

include( coupling_compiler_flags )
include( GNUInstallDirs )

################################################################################
# Dependencies
################################################################################

# jedi-cmake
find_package( jedicmake QUIET )

# eckit
find_package( eckit 1.11.6 REQUIRED )

# oops
find_package( oops 1.2.0 REQUIRED )

################################################################################
# Sources
################################################################################

add_subdirectory( test_mom6fv3 )
add_subdirectory( tools )

## Global Tests
ecbuild_add_test( TARGET coupling_coding_norms
                  TYPE SCRIPT
                  COMMAND ${CMAKE_BINARY_DIR}/bin/coupling_cpplint.py
                  ARGS --quiet --recursive ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

## Export package
ecbuild_install_project( NAME coupling )
ecbuild_print_summary()

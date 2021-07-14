# (C) Copyright 2021-2021 UCAR
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

set ( coupling_src_files
      TwoApplications.h
)

## Create Library target
ecbuild_add_library( TARGET   coupling
                     SOURCES  ${coupling_src_files}
                     INSTALL_HEADERS LISTED
                     HEADER_DESTINATION ${INSTALL_INCLUDE_DIR}/coupling
                     LINKER_LANGUAGE CXX )

## Link dependencies
target_link_libraries(coupling PUBLIC eckit)
target_link_libraries(coupling PUBLIC oops)

## Include paths
target_include_directories(coupling PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


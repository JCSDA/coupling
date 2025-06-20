# (C) Copyright 2024- UCAR.
#
# This software is licensed under the terms of the Apache Licence Version 2.0
# which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.

list( APPEND mom6_fv3_src_files
	ModelUFS.cc
	ModelUFS.h
)

## Create Library target
ecbuild_add_library( TARGET   coupled_mom6_fv3
                     SOURCES  ${mom6_fv3_src_files}
                     INSTALL_HEADERS LISTED
                     LINKER_LANGUAGE CXX
                    )

## Link dependencies
target_link_libraries(coupled_mom6_fv3 PUBLIC eckit)
target_link_libraries(coupled_mom6_fv3 PUBLIC fckit)
target_link_libraries(coupled_mom6_fv3 PUBLIC ioda)
target_link_libraries(coupled_mom6_fv3 PUBLIC oops)
target_link_libraries(coupled_mom6_fv3 PUBLIC fv3jedi)
target_link_libraries(coupled_mom6_fv3 PUBLIC soca)

## Include paths
target_include_directories(coupled_mom6_fv3 PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


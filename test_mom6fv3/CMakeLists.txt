set( coupling_mom6fv3_test_input
  testinput/soca_gridgen.yaml
  testinput/coupledgeometry.yaml
  testinput/coupledmodelaux.yaml
  testinput/coupledmodel.yaml
  testinput/forecast_fv3lm_mom6.yaml
)

set( coupling_mom6fv3_test_ref
  testref/forecast_fv3lm_mom6.ref
)

# create directories needed by coupling and symlink test yaml's
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testinput)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testref)
foreach(FILENAME ${coupling_mom6fv3_test_input})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testinput/${filename} )
endforeach(FILENAME)

################################################################################
# soca tests
################################################################################

add_subdirectory( executables )

# create directories needed by soca
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RESTART)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/INPUT)

set( soca_data_files
  ${soca_SOURCE_DIR}/test/Data/rossrad.dat
  ${soca_SOURCE_DIR}/test/Data/fields_metadata.yml
)

set( soca_model_param
  ${soca_SOURCE_DIR}/test/Data/workdir/diag_table
  ${soca_SOURCE_DIR}/test/Data/workdir/field_table
  ${soca_SOURCE_DIR}/test/Data/72x35x25/MOM_input
)

set( soca_model_namelist
  ${soca_SOURCE_DIR}/test/Data/72x35x25/input.nml
)

set( soca_model_restarts
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/forcing_daily.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/forcing_monthly.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/hycom1_25.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/layer_coord25.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/restarts/MOM.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/cice.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/sfc.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/ocean_hgrid.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/ocean_topog.nc
)

set( soca_test_ref
  ${soca_SOURCE_DIR}/test/testref/gridgen.test
)
# create static data directory, and symlink all files.
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
          ${soca_SOURCE_DIR}/test/Data
          ${CMAKE_CURRENT_BINARY_DIR}/data_static )

# symlink model config files
foreach(FILENAME ${soca_model_restarts})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/INPUT/${filename} )
endforeach(FILENAME)

# MOM's resource files
foreach(FILENAME ${soca_model_param} ${soca_data_files})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/${filename} )
endforeach(FILENAME)

# FMS input.nml that may be overwritten during the testing
foreach(FILENAME ${soca_model_namelist})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E copy
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/inputnml/${filename} )
endforeach(FILENAME)

# soca test ref files
foreach(FILENAME ${soca_test_ref})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testref/${filename} )
endforeach(FILENAME)

# Create soca geometry/grid
ecbuild_add_test( TARGET test_soca_gridgen
                  MPI 2
                  ARGS testinput/soca_gridgen.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_gridgen.x )

################################################################################
# fv3-jedi tests
################################################################################

# create directories needed by fv3-jedi
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testoutput)
#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/obs)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fv3files)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fieldsets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/forecast)
#file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/hofx)

# Ref files
foreach(FILENAME ${coupling_mom6fv3_test_ref})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testref/${filename} )
endforeach(FILENAME)

# FV3 config files
set( fv3jedi_test_fv3files
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/field_table
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/fmsmpp.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk64.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk72.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk127.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/input_gfs_c12.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/input_geos_c12.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/inputpert_4dvar.nml
)

# Field sets
set( fv3jedi_field_sets
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldsets/dynamics.yaml
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldsets/ufo.yaml
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldmetadata/gfs-restart.yaml
)

# Link to crtm coef files
# TODO relative path needs to go, depends on fv3jedi_get_crtm_test_data
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
                 ../../../fv3-jedi/test/Data/crtm
                 ${CMAKE_CURRENT_BINARY_DIR}/Data/crtm)

# Link restarts (gfs, geos, ...)
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
                 ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs
                 ${CMAKE_CURRENT_BINARY_DIR}/Data/inputs)

# Link fv3-jedi tier1 obs
#execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
#                 ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/obs
#                 ${CMAKE_CURRENT_BINARY_DIR}/Data/obs/testinput_tier_1)

# Test fv3lm forecast
foreach(FILENAME ${fv3jedi_field_sets})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/Data/fieldsets/${filename} )
endforeach(FILENAME)
foreach(FILENAME ${fv3jedi_test_fv3files})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/Data/fv3files/${filename} )
endforeach(FILENAME)

# fv3jedi yaml config files
foreach(FILENAME ${fv3jedi_test_yaml})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testinput/${filename} )
endforeach(FILENAME)

################################################################################
# Coupling tests
################################################################################

# Test CoupledGeometry class
ecbuild_add_test( TARGET  test_coupled_geometry_fv3_mom6
                  SOURCES executables/TestCoupledGeometry.cc
                  MPI 6
                  ARGS    "testinput/coupledgeometry.yaml"
                  LIBS    soca fv3jedi )

# Test CoupledModelAux class
ecbuild_add_test( TARGET  test_coupled_modelaux_fv3_mom6
                  SOURCES executables/TestCoupledModelAuxControl.cc
                  MPI 6
                  ARGS    "testinput/coupledmodelaux.yaml"
                  LIBS    soca fv3jedi )

# Test CoupledModelAux class
ecbuild_add_test( TARGET  test_coupled_model_fv3_mom6
                  SOURCES executables/TestCoupledModel.cc
                  MPI 6
                  ARGS    "testinput/coupledmodel.yaml"
                  LIBS    soca fv3jedi )

# Test CoupledForecast class
ecbuild_add_test( TARGET  test_coupled_forecast_fv3_mom6
                  MPI 6
                  COMMAND coupling_forecast_fv3_mom6.x
                  ARGS    "testinput/forecast_fv3lm_mom6.yaml" )

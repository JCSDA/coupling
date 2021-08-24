set( coupling_mom6fv3_test_input
  testinput/forecast_mom6_fv3lm.yaml
  testinput/forecast_mom6.yaml
  testinput/hofx_mom6_fv3lm.yaml
)

set( coupling_mom6fv3_test_ref
  testref/forecast_fv3lm.ref
  testref/hofx_fv3lm.ref
)

# create directories needed by coupling and symlink test yaml's
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testinput)
foreach(FILENAME ${coupling_mom6fv3_test_input})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testinput/${filename} )
endforeach(FILENAME)

################################################################################
# soca tests
################################################################################

# create directories needed by soca
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RESTART)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/INPUT)

set( soca_data_files
  ${soca_SOURCE_DIR}/test/Data/rossrad.dat
  ${soca_SOURCE_DIR}/test/Data/fields_metadata.yml
)

set( soca_model_param
  ${soca_SOURCE_DIR}/test/Data/72x35x25/diag_table
  ${soca_SOURCE_DIR}/test/Data/72x35x25/field_table
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
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/MOM.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/cice.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/sfc.res.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/ocean_hgrid.nc
  ${soca_SOURCE_DIR}/test/Data/72x35x25/INPUT/ocean_topog.nc
)

set( soca_test_yaml
  ${soca_SOURCE_DIR}/test/testinput/gridgen.yml
  ${soca_SOURCE_DIR}/test/testinput/hofx_4d.yml
)

set( soca_obs
  ${soca_SOURCE_DIR}/test/Data/Obs/adt.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/icec.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/icefb.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/prof.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/sss.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/sst.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/uocn_surface.nc
  ${soca_SOURCE_DIR}/test/Data/Obs/vocn_surface.nc
)

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

# soca yaml config files
foreach(FILENAME ${soca_test_yaml})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testinput/${filename} )
endforeach(FILENAME)

# soca obs
foreach(FILENAME ${soca_obs})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
         ${CMAKE_CURRENT_BINARY_DIR}/Data/${filename} )
endforeach(FILENAME)

# Create soca geometry/grid
ecbuild_add_test( TARGET test_soca_gridgen
                  MPI 2
                  ARGS testinput/gridgen.yml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_gridgen.x )

# Test mom6 solo forecast
ecbuild_add_test( TARGET test_soca_forecast
                  MPI 2
                  ARGS testinput/forecast_mom6.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_forecast.x )

# Test soca h(x) with mom6 solo
ecbuild_add_test( TARGET test_soca_hofx
                  MPI 2
                  ARGS testinput/hofx_4d.yml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_hofx.x )

################################################################################
# fv3-jedi tests
################################################################################

# create directories needed by fv3-jedi
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testoutput)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/obs)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fv3files)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fieldsets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/forecast)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/hofx)

# Ref files
foreach(FILENAME ${coupling_mom6fv3_test_ref})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/testoutput/${filename} )
endforeach(FILENAME)

# FV3 config files
set( fv3jedi_test_fv3files
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/field_table
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/fmsmpp.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk64.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk72.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/input_gfs_c12.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/input_geos_c12.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/inputpert_4dvar.nml
)

# Field sets
set( fv3jedi_field_sets
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldsets/dynamics.yaml
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldsets/ufo.yaml
)

set( fv3jedi_test_yaml
  ${fv3jedi_SOURCE_DIR}/test/testinput/forecast_fv3lm.yaml
  ${fv3jedi_SOURCE_DIR}/test/testinput/hofx_fv3lm.yaml
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
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
                 ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/obs
                 ${CMAKE_CURRENT_BINARY_DIR}/Data/obs/testinput_tier_1)

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

# Test fv3lm forecast
ecbuild_add_test( TARGET test_fv3jedi_forecast
                  MPI 6
                  ARGS testinput/forecast_fv3lm.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/fv3jedi_forecast.x )

# Test fv3-jedi h(x) with fv3lm/geos
ecbuild_add_test( TARGET test_fv3jedi_hofx
                  MPI 6
                  ARGS testinput/hofx_fv3lm.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/fv3jedi_hofx.x )

################################################################################
# Coupling tests
################################################################################

ecbuild_add_test( TARGET  test_forecast_mom6_fv3lm
                  MPI 12
                  COMMAND forecast_mom6_fv3.x
                  ARGS    testinput/forecast_mom6_fv3lm.yaml
                  TEST_DEPENDS test_soca_forecast test_fv3jedi_forecast  )

ecbuild_add_test( TARGET  test_hofx_mom6_fv3lm
                  MPI 12
                  COMMAND hofx_mom6_fv3.x
                  ARGS    testinput/hofx_mom6_fv3lm.yaml
                  TEST_DEPENDS test_soca_hofx test_fv3jedi_hofx  )

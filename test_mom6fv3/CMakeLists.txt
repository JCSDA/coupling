set( coupling_mom6fv3_test_input
  testinput/forecast_mom6_fv3lm.yaml
  testinput/forecast_mom6.yaml
)

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

set( soca_data_files
  ${soca_SOURCE_DIR}/test/Data/godas_sst_bgerr.nc
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
)

# Create Data directory for model input and symlink all files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/INPUT)
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

# MOM's output directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RESTART)

# Create soca geometry/grid
ecbuild_add_test( TARGET test_soca_gridgen
                  MPI 2
                  ARGS testinput/gridgen.yml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_gridgen.x )

# soca forecast output directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data)
ecbuild_add_test( TARGET test_soca_forecast
                  MPI 2
                  ARGS testinput/forecast_mom6.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/soca_forecast.x )

################################################################################
# fv3-jedi tests
################################################################################

# FV3 config files
set( fv3jedi_test_fv3files
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/field_table
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/fmsmpp.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/akbk64.nc4
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/input_gfs_c12.nml
  ${fv3jedi_SOURCE_DIR}/test/Data/fv3files/inputpert_4dvar.nml
)

# Field sets
set( fv3jedi_field_sets
  ${fv3jedi_SOURCE_DIR}/test/Data/fieldsets/dynamics.yaml
)

# Restarts
set( fv3jedi_restarts
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.coupler.res
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile1.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile2.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile3.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile4.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile5.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_core.res.tile6.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile1.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile2.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile3.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile4.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile5.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_tracer.res.tile6.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile1.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile2.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile3.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile4.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile5.nc
  ${fv3_jedi_data_SOURCE_DIR}/testinput_tier_1/inputs/gfs_c12/bkg/20180414.210000.fv_srf_wnd.res.tile6.nc
)

set( fv3jedi_test_yaml
  ${fv3jedi_SOURCE_DIR}/test/testinput/forecast_fv3lm.yaml
)

# Test fv3lm forecast
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fv3files)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/fieldsets)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/inputs/gfs_c12/bkg)
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
foreach(FILENAME ${fv3jedi_restarts})
     get_filename_component(filename ${FILENAME} NAME )
     execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/Data/inputs/gfs_c12/bkg/${filename} )
endforeach(FILENAME)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Data/forecast)
ecbuild_add_test( TARGET test_fv3jedi_forecast
                  MPI 6
                  ARGS testinput/forecast_fv3lm.yaml
                  COMMAND ${CMAKE_BINARY_DIR}/bin/fv3jedi_forecast.x )

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

ecbuild_add_test( TARGET  test_forecast_mom6_fv3lm
                  MPI 12
                  COMMAND forecast_mom6_fv3.x
                  ARGS    testinput/forecast_mom6_fv3lm.yaml
                  TEST_DEPENDS test_soca_forecast test_fv3jedi_forecast  )

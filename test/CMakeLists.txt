
list( APPEND coupled_testinput
  forecast_qg_l95.yaml
  hofx_l95_l95.yaml
  hofx_qg_l95.yaml
)

list( APPEND coupled_testoutput
  forecast_qg_l95.test
  hofx_l95_l95.test
  hofx_qg_l95.test
)

# Create Data directory for test input and symlink all files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testinput)
foreach(FILENAME ${coupled_testinput})
    execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME} )
endforeach(FILENAME)

# Create Data directory for reference output and symlink all files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testoutput)
foreach(FILENAME ${coupled_testoutput})
    execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink
           ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
           ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME} )
endforeach(FILENAME)

# Create Data directory for test data
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/TestData)

#####################################################################
# coupled forecast tests
#####################################################################

ecbuild_add_test( TARGET  test_forecast_qg_l95
                  COMMAND forecast_qg_l95.x
                  ARGS    forecast_qg_l95.yaml
                  TEST_DEPENDS test_l95_forecast test_qg_forecast )

#####################################################################
# obs-related tests
#####################################################################

ecbuild_add_test( TARGET  test_hofx_l95_l95
                  COMMAND hofx_l95_l95.x
                  ARGS    hofx_l95_l95.yaml
                  TEST_DEPENDS test_l95_truth test_l95_makeobs4d )

ecbuild_add_test( TARGET  test_hofx_qg_l95
                  COMMAND hofx_qg_l95.x
                  ARGS    hofx_qg_l95.yaml
                  TEST_DEPENDS test_qg_truth test_qg_makeobs4d )


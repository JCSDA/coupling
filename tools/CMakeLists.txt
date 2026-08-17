
list( APPEND test_files
  cpplint.py
)

file( MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
foreach(FILENAME ${test_files})
  file( COPY_FILE
     ${PROJECT_SOURCE_DIR}/tools/${FILENAME}
     ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}_${FILENAME} ONLY_IF_DIFFERENT )
endforeach(FILENAME)


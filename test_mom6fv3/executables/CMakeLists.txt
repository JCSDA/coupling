ecbuild_add_executable( TARGET  coupling_forecast_fv3_mom6.x
                        SOURCES forecast_fv3_mom6.cc
                        LIBS    soca
                                fv3jedi
                      )


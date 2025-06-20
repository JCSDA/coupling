ecbuild_add_executable( TARGET  coupling_forecast_fv3_mom6.x
                        SOURCES forecast_fv3_mom6.cc
                        LIBS    soca
                                fv3jedi
				coupled_mom6_fv3
                      )

ecbuild_add_executable( TARGET  coupling_hofx3d_fv3_mom6.x
                        SOURCES hofx3d_fv3_mom6.cc
                        LIBS    soca
                                fv3jedi
				coupled_mom6_fv3
                      )


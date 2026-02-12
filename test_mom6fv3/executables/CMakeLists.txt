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

ecbuild_add_executable( TARGET  coupling_interp_fv3_mom6.x
                        SOURCES interp_fv3_mom6.cc
                        LIBS    soca
                                fv3jedi
				coupled_mom6_fv3
                      )

ecbuild_add_executable( TARGET  coupling_var_fv3_mom6.x
                        SOURCES var_fv3_mom6.cc
                        LIBS    soca
                                fv3jedi
                      )

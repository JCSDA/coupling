
ecbuild_add_executable( TARGET  forecast_qg_l95.x
                        SOURCES forecast_qg_l95.cc
                        LIBS    coupling qg lorenz95 )

ecbuild_add_executable( TARGET  hofx_l95_l95.x
                        SOURCES hofx_l95_l95.cc
                        LIBS    coupling lorenz95 )

ecbuild_add_executable( TARGET  hofx_qg_l95.x
                        SOURCES hofx_qg_l95.cc
                        LIBS    coupling lorenz95 qg )

ecbuild_add_executable( TARGET  forecast_mom6_fv3.x
                        SOURCES forecast_mom6_fv3.cc
                        LIBS    coupling soca fv3jedi )


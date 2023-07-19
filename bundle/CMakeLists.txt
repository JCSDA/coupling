# (C) COPYRIGHT 2021-2021 UCAR
#
# THIS SOFTWARE IS LICENSED UNDER THE TERMS OF THE APACHE LICENCE VERSION 2.0
# WHICH CAN BE OBTAINED AT HTTP://WWW.APACHE.ORG/LICENSES/LICENSE-2.0.

#
# bundle for coupling
#

cmake_minimum_required( VERSION 3.12)
project( coupling-bundle VERSION 0.0.0 LANGUAGES C CXX Fortran )

find_package( ecbuild 3.6 QUIET)
include( ecbuild_bundle )
ecbuild_bundle_initialize()

# jedi-cmake
#ecbuild_bundle( PROJECT jedicmake GIT "https://github.com/jcsda-internal/jedi-cmake.git" UPDATE BRANCH develop RECURSIVE )
#include( jedicmake/cmake/Functions/git_functions.cmake  )

#===================================================================================================
# required repositories
#===================================================================================================

ecbuild_bundle( PROJECT oops            GIT "https://github.com/jcsda-internal/oops.git"            UPDATE BRANCH develop )
ecbuild_bundle( PROJECT vader           GIT "https://github.com/jcsda-internal/vader.git"           UPDATE BRANCH develop )
ecbuild_bundle( PROJECT saber           GIT "https://github.com/jcsda-internal/saber.git"           UPDATE BRANCH develop )
ecbuild_bundle( PROJECT ioda            GIT "https://github.com/jcsda-internal/ioda.git"            UPDATE BRANCH develop )
ecbuild_bundle( PROJECT gsw             GIT "https://github.com/jcsda-internal/GSW-Fortran.git"     UPDATE BRANCH develop )
ecbuild_bundle( PROJECT crtm            GIT "https://github.com/JCSDA/CRTMv3.git"                   UPDATE BRANCH develop )
ecbuild_bundle( PROJECT ufo             GIT "https://github.com/jcsda-internal/ufo.git"             UPDATE BRANCH feature/no_crtm_for_misval_sst )


#===================================================================================================
# Optional Model Interfaces
#===================================================================================================

option(BUILD_SOCA "download and build soca" ON)
if ( BUILD_SOCA)
  ecbuild_bundle( PROJECT mom6 GIT "https://github.com/jcsda-internal/MOM6.git"            UPDATE BRANCH main-ecbuild RECURSIVE )
  ecbuild_bundle( PROJECT soca GIT "https://github.com/jcsda-internal/soca.git"            UPDATE BRANCH develop )
endif ()

option(BUILD_FV3JEDI "download and build fv3-jedi" ON)
if ( BUILD_FV3JEDI)
  ecbuild_bundle( PROJECT fv3         GIT "https://github.com/jcsda/GFDL_atmos_cubed_sphere.git"          BRANCH release-stable UPDATE )
  ecbuild_bundle( PROJECT femps       GIT "https://github.com/jcsda-internal/femps.git"                   BRANCH develop UPDATE )
  ecbuild_bundle( PROJECT fv3-jedi-lm GIT "https://github.com/jcsda-internal/fv3-jedi-linearmodel.git"    BRANCH develop UPDATE )
  ecbuild_bundle( PROJECT fv3-jedi    GIT "https://github.com/jcsda-internal/fv3-jedi.git"                BRANCH develop UPDATE )
  ecbuild_bundle( PROJECT fv3-jedi-data GIT "https://github.com/JCSDA-internal/fv3-jedi-data.git"         BRANCH develop UPDATE )
endif ()

ecbuild_bundle( PROJECT coupling    SOURCE "../" )

#===================================================================================================

ecbuild_bundle_finalize()

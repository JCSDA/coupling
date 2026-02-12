/*
 * (C) Copyright 2025- UCAR
 * (C) Copyright 2025- NOAA/EMC
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"
#include "ufo/ObsTraits.h"

#include "oops/base/ModelSpaceCovarianceBase.h"

#include "oops/coupled/BlockDiagonalCovarianceCoupled.h"
#include "oops/coupled/GetValuesCoupled.h"
#include "oops/coupled/TraitCoupled.h"

#include "oops/runs/Variational.h"
#include "oops/runs/Run.h"

#include "saber/oops/instantiateCovarFactory.h"

#include "ufo/instantiateObsFilterFactory.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);
  ufo::instantiateObsFilterFactory();
  saber::instantiateCovarFactory<fv3jedi::Traits>();
  saber::instantiateCovarFactory<soca::Traits>();
  saber::instantiateCovarFactory<oops::TraitCoupled<fv3jedi::Traits, soca::Traits> >();
  static oops::CovarMaker<oops::TraitCoupled<fv3jedi::Traits, soca::Traits>,
      oops::BlockDiagonalCovarianceCoupled<fv3jedi::Traits, soca::Traits> >  makerCoupled_("Coupled Block Diagonal");
  oops::Variational<oops::TraitCoupled<fv3jedi::Traits, soca::Traits>,
                    ufo::ObsTraits> var;

  return run.execute(var);
}

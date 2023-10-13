/*
 * (C) Copyright 2023- UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"
#include "ufo/ObsTraits.h"

#include "oops/coupled/GetValuesCoupled.h"
#include "oops/coupled/TraitCoupled.h"

#include "oops/runs/HofX3D.h"
#include "oops/runs/Run.h"

#include "ufo/instantiateObsErrorFactory.h"
#include "ufo/instantiateObsFilterFactory.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);
  ufo::instantiateObsErrorFactory();
  ufo::instantiateObsFilterFactory();
  oops::HofX3D<oops::TraitCoupled<fv3jedi::Traits, soca::Traits>,
               ufo::ObsTraits> hofx;

  return run.execute(hofx);
}

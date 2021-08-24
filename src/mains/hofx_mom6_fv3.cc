/*
 * (C) Copyright 2021-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"

#include "oops/runs/HofX4D.h"
#include "oops/runs/Run.h"
#include "ufo/instantiateObsErrorFactory.h"
#include "ufo/instantiateObsFilterFactory.h"
#include "ufo/ObsTraits.h"

#include "coupling/TwoApplications.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);
  ufo::instantiateObsErrorFactory<ufo::ObsTraits>();
  ufo::instantiateObsFilterFactory<ufo::ObsTraits>();
  oops::TwoApplications<oops::HofX4D<soca::Traits, ufo::ObsTraits>,
                        oops::HofX4D<fv3jedi::Traits, ufo::ObsTraits>                 > apps;

  return run.execute(apps);
}

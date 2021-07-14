/*
 * (C) Copyright 2021-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "../../l95/src/lorenz95/L95Traits.h"
#include "../../qg/model/QgTraits.h"

#include "oops/runs/HofX4D.h"
#include "oops/runs/Run.h"

#include "coupling/TwoApplications.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);

  oops::TwoApplications<oops::HofX4D<lorenz95::L95Traits, lorenz95::L95ObsTraits>,
                        oops::HofX4D<qg::QgTraits, qg::QgObsTraits>                 > apps;

  return run.execute(apps);
}


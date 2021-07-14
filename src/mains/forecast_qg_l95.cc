/*
 * (C) Copyright 2021-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "../../l95/src/lorenz95/L95Traits.h"
#include "../../qg/model/QgTraits.h"

#include "oops/generic/instantiateModelFactory.h"
#include "oops/runs/Forecast.h"
#include "oops/runs/Run.h"

#include "coupling/TwoApplications.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);

  oops::instantiateModelFactory<qg::QgTraits>();
  oops::instantiateModelFactory<lorenz95::L95Traits>();

  oops::TwoApplications< oops::Forecast<lorenz95::L95Traits>,
                         oops::Forecast<qg::QgTraits>          > apps;

  return run.execute(apps);
}


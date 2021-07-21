/*
 * (C) Copyright 2021-2021 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "oops/qg/model/QgTraits.h"
#include "soca/Traits.h"

#include "oops/generic/instantiateModelFactory.h"
#include "oops/runs/Forecast.h"
#include "oops/runs/Run.h"

#include "coupling/TwoApplications.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);

  oops::instantiateModelFactory<soca::Traits>();
  oops::instantiateModelFactory<qg::QgTraits>();

  oops::TwoApplications< oops::Forecast<soca::Traits>,
                         oops::Forecast<qg::QgTraits>          > apps;

  return run.execute(apps);
}

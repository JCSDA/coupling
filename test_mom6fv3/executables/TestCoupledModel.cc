/*
 * (C) Copyright 2021- UCAR.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"

#include "oops/coupled/instantiateCoupledFactory.h"
#include "oops/coupled/TraitCoupled.h"
#include "oops/generic/instantiateModelFactory.h"
#include "oops/runs/Run.h"

#include "test/interface/Model.h"

int main(int argc, char ** argv) {
  oops::Run run(argc, argv);
  oops::instantiateModelFactory<fv3jedi::Traits>();
  oops::instantiateModelFactory<soca::Traits>();
  oops::instantiateCoupledFactory<fv3jedi::Traits, soca::Traits>();
  test::Model<oops::TraitCoupled<fv3jedi::Traits, soca::Traits>> tests;
  return run.execute(tests);
}

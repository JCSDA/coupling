/*
 * (C) Copyright 2025- UCAR
 * (C) Copyright 2025- NOAA/EMC
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */
 
#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"

#include "oops/runs/InterpolateStateBetweenModels.h"
#include "oops/runs/Run.h"

int main(int argc,  char ** argv) {
  oops::Run run(argc, argv);
  oops::InterpolateStateBetweenModels<soca::Traits, fv3jedi::Traits> interp;
  return run.execute(interp);
}
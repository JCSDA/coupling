/*
 * (C) Copyright 2024 UCAR-
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "ModelUFS.h"

#include "eckit/config/Configuration.h"

#include "fv3jedi/Geometry/Geometry.h"
#include "fv3jedi/State/State.h"
#include "soca/Geometry/Geometry.h"
#include "soca/State/State.h"

namespace coupled_mom6_fv3 {

// -------------------------------------------------------------------------------------------------
ModelUFS::ModelUFS(const GeometryCoupled_ & geometry, const eckit::Configuration & config)
  : tstep_(util::Duration(config.getString("time step")))
{
  oops::Log::info() << "Creating ModelUFS with: " << std::endl;
  oops::Log::info() << " fv3 geometry: " << geometry.geometry1() << std::endl;
  oops::Log::info() << " soca geometry: " << geometry.geometry2() << std::endl;
  oops::Log::info() << " config: " << config << std::endl;
}

// -------------------------------------------------------------------------------------------------
void ModelUFS::initialize(StateCoupled_ & xx) const {
  oops::Log::trace() << "ModelUFS::initialize starting" << std::endl;
  // TODO(someone): Initialize code here, access fv3-jedi state as xx.state1(),
  // soca state as xx.state2()
  oops::Log::trace() << "ModelUFS::initialize done" << std::endl;
}
// -------------------------------------------------------------------------------------------------
void ModelUFS::step(StateCoupled_ & xx, const ModelBiasCoupled_ &) const
{
  oops::Log::trace() << "ModelUFS::step starting" << std::endl;
  // TODO(someone): call the coupled model, propagate state in time.
  xx.updateTime(tstep_);
  oops::Log::trace() << "ModelUFS::step done" << std::endl;
}
// -------------------------------------------------------------------------------------------------
void ModelUFS::finalize(StateCoupled_ & xx) const {
  oops::Log::trace() << "ModelUFS::finalize starting" << std::endl;
  // TODO(someone): finalize the forecast here.
  oops::Log::trace() << "ModelUFS::finalize done" << std::endl;
}
// -------------------------------------------------------------------------------------------------
void ModelUFS::print(std::ostream & os) const {
  os << "Coupled UFS propagating soca and fv3-jedi states";
}
// -------------------------------------------------------------------------------------------------
}  // namespace coupled_mom6_fv3

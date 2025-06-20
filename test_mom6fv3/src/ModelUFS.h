/*
 * (C) Copyright 2024- UCAR.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#pragma once

#include <ostream>
#include <string>

#include "oops/interface/ModelBase.h"
#include "oops/util/Duration.h"
#include "oops/util/ObjectCounter.h"

#include "oops/coupled/GeometryCoupled.h"
#include "oops/coupled/StateCoupled.h"
#include "oops/coupled/TraitCoupled.h"

#include "fv3jedi/Utilities/Traits.h"
#include "soca/Traits.h"

// Forward declarations
namespace eckit {
  class Configuration;
}

namespace coupled_mom6_fv3 {

// -------------------------------------------------------------------------------------------------
class ModelUFS: public oops::interface::ModelBase<oops::TraitCoupled<fv3jedi::Traits, soca::Traits>>,
                private util::ObjectCounter<ModelUFS> {
  typedef oops::GeometryCoupled<fv3jedi::Traits, soca::Traits>  GeometryCoupled_;
  typedef oops::StateCoupled<fv3jedi::Traits, soca::Traits>     StateCoupled_;
  typedef oops::AuxCoupledModel<fv3jedi::Traits, soca::Traits>  ModelBiasCoupled_;
 public:
  static const std::string classname() {return "coupled_mom6_fv3::ModelUFS";}

  ModelUFS(const GeometryCoupled_ &, const eckit::Configuration &);

  void initialize(StateCoupled_ &) const;
  void step(StateCoupled_ &, const ModelBiasCoupled_ &) const;
  void finalize(StateCoupled_ &) const;

  const util::Duration & timeResolution() const {return tstep_;}

 private:
  void print(std::ostream &) const;
  const util::Duration tstep_;
};
// -----------------------------------------------------------------------------

}  // namespace coupled_mom6_fv3

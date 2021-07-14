/*
 * (C) Copyright 2018-2020 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#pragma once

#include <string>
#include <vector>

#include "eckit/config/LocalConfiguration.h"
#include "eckit/config/YAMLConfiguration.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/mpi/Comm.h"
#include "oops/mpi/mpi.h"
#include "oops/runs/Application.h"
#include "oops/util/Logger.h"

namespace oops {

template <typename APP1, typename APP2>
class TwoApplications : public Application {
 public:
// -----------------------------------------------------------------------------
  explicit TwoApplications(const eckit::mpi::Comm & comm = oops::mpi::world()) :
      Application(comm) {}
// -----------------------------------------------------------------------------
  virtual ~TwoApplications() {}
// -----------------------------------------------------------------------------
  int execute(const eckit::Configuration & fullConfig) const {
//  Get the list of yaml files
    std::vector<std::string> listConf;
    fullConfig.get("files", listConf);
    Log::info() << "TwoApplications yaml files:" << listConf << std::endl;
    ASSERT(listConf.size() == 2);

//  Get the MPI partition
    const int ntasks = this->getComm().size();
    ASSERT(ntasks%2 == 0);
    const int mytask = this->getComm().rank();
    const int tasks_per_app = ntasks / 2;
    const int myapp = mytask / tasks_per_app + 1;

//  Create communicator for each app, named comm_app_1 and comm_app_2
    std::string commNameStr = "comm_app_" + std::to_string(myapp);
    char const *commName = commNameStr.c_str();
    eckit::mpi::Comm & commApp = this->getComm().split(myapp, commName);

//  Each app uses a different configuration:
    eckit::PathName confPath = listConf[myapp-1];
    eckit::YAMLConfiguration appConf(confPath);
    int ierr = 0;

//  Run the 2 apps in parallel
    if (myapp == 1) {
      APP1 app1a(commApp);
      ierr = app1a.execute(appConf);
    } else {
      APP2 app2a(commApp);
      ierr = app2a.execute(appConf);
    }

//  Would be nice to run the two apps on all procs one after the other
//  but that requires different configurations
//  could even create those apps before the ones running in parallel to check apps
//  can exist at the same time
/*
    APP1 app1b(this->getComm());
    ierr = app1b.execute(appConf);

    APP2 app2b(this->getComm());
    ierr = app2b.execute(appConf);
*/

    return ierr;
  }
// -----------------------------------------------------------------------------
 private:
  std::string appname() const {
    return "oops::TwoApplications<>";
  }
// -----------------------------------------------------------------------------
};

}  // namespace oops


#ifndef SUBSYSTEM_INTERFACES_H_
#define SUBSYSTEM_INTERFACES_H_

// include all interfaces
#include "catapult_interface.hpp"
#include "chassis_interface.hpp"
#include "intake_interface.hpp"
#include "lift_interface.hpp"
#include "scraper_brake_interface.hpp"

namespace interfaces {

  // import all namespaces
  using namespace catapult_interface;
  using namespace chassis_interface;
  using namespace intake_interface;
  using namespace lift_interface;
  using namespace scraper_interface;

  // update all interfaces
  void update();
}

#endif
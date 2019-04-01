#ifndef LIFT_CONTROLLER_H_
#define LIFT_CONTROLLER_H_

#include "subsystem_interfaces/lift_interface.hpp"

namespace lift_controller {

  // go to position
  void goto_angle(units::Angle angle, bool wait=true, units::Angle threshold=2*units::DEGREES);
  void goto_height(units::Distance height, bool wait=true, units::Distance threshold=.25*units::INCHES);
}

#endif

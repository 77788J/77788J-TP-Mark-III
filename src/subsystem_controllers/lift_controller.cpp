#include "subsystem_controllers/lift_controller.hpp"

namespace lift_controller {

  // go to angle
  void goto_angle(units::Angle angle, bool wait, units::Angle threshold) {

    // move
    lift_interface::move_position_angular(angle);

    // wait
    if (wait) while (fabs(lift_interface::get_angle() - angle) > threshold) pros::delay(10);
  }
  

  // go to height
  void goto_height(units::Distance height, bool wait, units::Distance threshold) {

    // move
    lift_interface::move_position_linear(height);

    // wait
    if (wait) while (fabs(lift_interface::get_height() - height) > threshold) pros::delay(10);
  }
}


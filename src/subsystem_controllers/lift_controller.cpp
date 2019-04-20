#include "subsystem_controllers/lift_controller.hpp"

namespace lift_controller {

  units::Angle angle_target = lift_interface::ANGLE_MIN;
  bool custom_enabled = true;

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


  // goto angle (custom controller)
  void goto_angle_custom(units::Angle angle, bool wait, units::Angle threshold) {
    angle_target = angle;
    custom_enabled = true;

    // wait
    if (wait) while (fabs(lift_interface::get_angle() - angle) > threshold) pros::delay(10);
  }

  // update
  void update() {
    units::Angle error = angle_target - lift_interface::get_angle();

    lift_interface::move_voltage(1000 * cos(lift_interface::get_angle()) + error * 32000);
  }
}


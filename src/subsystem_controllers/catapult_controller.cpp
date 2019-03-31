#include "subsystem_controllers/catapult_controller.hpp"

namespace catapult_controller {

  // voltage to be set when in override mode
  int override_voltage = 0;

  // is currently overrided
  bool is_overriden = false;

  // target angle of slipgear
  units::Angle slipgear_target = 0 * units::DEGREES;


  // fire catapult
  void fire(bool wait_for_fire) {
    slipgear_target += 360;
    set_override(false);

    if (wait_for_fire) while (catapult_interface::get_angle_slipgear() > 5 * units::DEGREES) pros::delay(10);
  }


  // set override
  void set_override(bool _override) {
    is_overriden = _override;
  }


  // wait for catapult to be at load angle
  void wait_for_load_angle(units::Angle tolerance, units::Time timeout) {
    units::Time t = pros::millis() * units::MS;
    while (!get_at_load_angle(tolerance) && pros::millis() - t < timeout) {pros::delay(10);}
  }


  // update controller
  void update() {
    if (is_overriden) catapult_interface::move_voltage(override_voltage);
    else catapult_interface::move_position_slipgear(slipgear_target);
  }
}

#include "subsystem_controllers/catapult_controller.hpp"
#include "subsystem_controllers/intake_controller.hpp"
#include "subsystem_controllers/lift_controller.hpp"

namespace catapult_controller {

  // voltage to be set when in override mode
  int override_voltage = 0;

  // is currently overrided
  bool is_overriden = false;

  bool is_shooting = false;

  // target angle of slipgear
  units::Angle slipgear_target = 85 * units::DEGREES;


  // fire catapult
  void fire(bool wait_for_fire) {
    // slipgear_target += 180 * units::DEGREES;
    // slipgear_target = 165 - catapult_interface::get_angle_slipgear(false);
    // catapult_interface::motor.tare_position();
    set_override(false);
    is_shooting = true;

    if (wait_for_fire) {
      while (catapult_interface::limit.get_value()) pros::delay(10);
      intake_controller::balls_loaded = 0;
      intake_controller::balls_in_possession = 0;
      while (!catapult_interface::limit.get_value()) pros::delay(10);
    }
    intake_controller::balls_loaded = 0;
    intake_controller::balls_in_possession = 0;
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
    else if (is_shooting) {
      catapult_interface::move_voltage(12000);
      if (!catapult_interface::limit.get_value()) is_shooting = false;
    }
    else if (catapult_interface::limit.get_value()) catapult_interface::motor.move_velocity(0);
    else catapult_interface::move_voltage(12000);
  }
}

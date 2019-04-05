#include "subsystem_interfaces/interfaces.hpp"

namespace interfaces {
  
  void initialize() {
    catapult_interface::motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lift_interface::motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    intake_interface::motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    scraper_interface::motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
}
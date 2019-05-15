#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

void autons::auto_red_cap(bool park) {

  chassis_controller::PidConstants slow_decel = {
    .kp = 960,
    .ki = 10,
    .kd = -250000,
    .max_accel = 320,
    .max_voltage = 12000,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants slow_move = {
    .kp = 960,
    .ki = 10,
    .kd = -250000,
    .max_accel = 320,
    .max_voltage = 4500,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants slow_orientation = {
    .kp = 5600,
    .ki = 15,
    .kd = -74,
    .max_accel = 250,
    .max_voltage = 12000,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants with_cap = {
    .kp = 4900,
    .ki = 15,
    .kd = -74,
    .max_accel = 250,
    .max_voltage = 6000,
    .min_voltage = 2500
  };

  chassis_interface::reset_orientation(0 * units::DEGREES);

  // move to cap and get ball
  catapult_controller::override_voltage = 0;
  catapult_controller::set_override(true);
  intake_controller::set_mode(intake_controller::succ_hold);
  chassis_controller::move_dist_pid(38 * units::INCHES, slow_decel);
  intake_controller::set_mode(intake_controller::succ_hold);

  // pick up other cap
  chassis_controller::rotate_pid(96 * units::DEGREES, slow_orientation);
  chassis_interface::reset_dist_linear(0);
  chassis_controller::move_dist_pid(-12 * units::INCHES, slow_move);
  lift_controller::goto_angle_custom(lift_interface::ANGLE_EXTEND, false);
  pros::delay(250);

  // move up and turn
  chassis_controller::move_dist_pid((-6.9 * units::INCHES) - chassis_interface::get_dist_linear());
  catapult_controller::set_override(false);
  chassis_controller::rotate_pid(192.5 * units::DEGREES, with_cap);

  // stack
  chassis_controller::mode = chassis_controller::none;
  chassis_interface::move_voltage(12000);
  pros::delay(750);
  chassis_interface::move_voltage(-100, -100);
  pros::delay(10);
  chassis_interface::move_voltage(3000);
  while (fabs(chassis_interface::get_vel_linear()) > 10 * units::RPM) pros::delay(10);
  chassis_interface::move_voltage(0);
  chassis_interface::reset_orientation(180 * units::DEGREES);
  chassis_controller::move_dist_pid(-2 * units::INCHES);
  lift_controller::goto_angle_custom(lift_interface::ANGLE_MAX, false);
  pros::delay(690);
  chassis_controller::move_dist_pid(-7 * units::INCHES);
  lift_controller::goto_angle_custom(lift_interface::ANGLE_MIN, false);
  chassis_controller::rotate_pid(45 * units::DEGREES);
  chassis_controller::move_dist_pid(-8 * units::INCHES);
  catapult_controller::fire(true);
  intake_controller::set_mode(intake_controller::succ);
  pros::delay(1000);
  chassis_controller::move_dist_pid(24 * units::INCHES);
  catapult_controller::fire();
  
}
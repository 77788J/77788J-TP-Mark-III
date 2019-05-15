#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

void autons::auto_red_3_flag(bool park) {

  chassis_interface::reset_orientation(90 * units::DEGREES);

  chassis_controller::PidConstants slow_decel = {
    .kp = 1300,
    .ki = 10,
    .kd = -280000,
    .max_accel = 320,
    .max_voltage = 12000,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants slow = {
    .kp = 2000,
    .ki = 10,
    .kd = -280000,
    .max_accel = 320,
    .max_voltage = 8000,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants slow_turn = {
    .kp = 7500,
    .ki = 15,
    .kd = -69,
    .max_accel = 250,
    .max_voltage = 6500,
    .min_voltage = 2500
  };

  int start = pros::millis();

  // get bottom flag
  chassis_controller::move_dist_pid(32.5 * units::INCHES, slow_decel);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP, false);
  pros::delay(250);
  chassis_controller::move_dist_pid(16 * units::INCHES - chassis_interface::get_dist_linear(), slow);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);

  // turn and scrape
  chassis_controller::rotate_pid(0 * units::DEGREES, slow_turn);
  chassis_interface::reset_dist_linear();
  chassis_controller::move_dist_pid(7 * units::INCHES, slow);
  intake_controller::set_mode(intake_controller::succ_hold);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP, false);
  pros::delay(250);
  chassis_controller::move_dist_pid(1.5 * units::INCHES - chassis_interface::get_dist_linear(), slow);

  // flip cap and shoot flag
  chassis_controller::move_dist_pid(20 * units::INCHES - chassis_interface::get_dist_linear(), slow);
  scraper_interface::max_voltage = 9000;
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);
  pros::delay(250);
  scraper_interface::max_voltage = 12000;
  chassis_controller::rotate_pid(41 * units::DEGREES, slow_turn);
  catapult_controller::fire(true);

  // scrape off platform
  chassis_controller::rotate_pid(-80 * units::DEGREES, slow_turn);
  chassis_interface::reset_dist_linear();
  pros::delay(20);
  chassis_controller::move_dist_pid(26 * units::INCHES - chassis_interface::get_dist_linear(), slow);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_SCRAPE, false);
  pros::delay(250);
  intake_controller::set_mode(intake_controller::succ);
  chassis_controller::move_dist_pid(-8.25 * units::INCHES, slow);
  intake_controller::set_mode(intake_controller::succ_hold);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);

  // shoot
  chassis_controller::rotate_pid(-180 * units::DEGREES, slow_turn);
  intake_controller::set_mode(intake_controller::succ);
  chassis_controller::move_dist_pid(20.5 * units::INCHES, slow);
  chassis_controller::rotate_pid(-273.5 * units::DEGREES, slow_turn);
  while (pros::millis() - start < 14500) pros::delay(10);
  catapult_controller::fire();

}
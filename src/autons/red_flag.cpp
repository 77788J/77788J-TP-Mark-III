#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

void autons::auto_red_flag(bool park) {

  chassis_controller::PidConstants slow_decel = {
    .kp = 980,
    .ki = 10,
    .kd = -280000,
    .max_accel = 320,
    .max_voltage = 12000,
    .min_voltage = 2500
  };

  chassis_controller::PidConstants slow_orientation = {
    .kp = 5500,
    .ki = 15,
    .kd = -69,
    .max_accel = 250,
    .max_voltage = 12000,
    .min_voltage = 2500
  };

  // move to cap and scrape
  chassis_controller::move_dist_pid(17.3 * units::INCHES);

  // shoot catapult
  while (!catapult_interface::limit.get_value()) pros::delay(10);
  catapult_controller::fire();

  // scraper down
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP, false);
  pros::delay(250);

  // pull back and scrape
  intake_controller::set_mode(intake_controller::succ);
  chassis_controller::move_dist_pid(-2.75 * units::INCHES);
  pros::delay(500);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);
  chassis_controller::move_dist_pid(-chassis_interface::get_dist_linear() - 2 * units::INCHES);

  // rotate to flags
  chassis_controller::rotate_pid(89 * units::DEGREES);

  // shoot
  intake_controller::set_mode(intake_controller::off);
  catapult_controller::fire(true);

  // go to platform
  chassis_controller::rotate_pid(-30 * units::DEGREES);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);
  chassis_controller::move_dist_pid(21 * units::INCHES);

  // scrape platform
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP, false);
  intake_controller::set_mode(intake_controller::succ);
  pros::delay(250);
  chassis_controller::rotate_pid(-40 * units::DEGREES);
  chassis_controller::move_dist_pid(-18 * units::INCHES);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);

  // goto cap
  chassis_controller::rotate_pid(1.69 * units::DEGREES);
  chassis_controller::move_dist_pid(46 * units::INCHES, slow_decel);

  // rotate and shoot
  chassis_controller::rotate_pid(92 * units::DEGREES, slow_orientation);
  pros::delay(250);
  catapult_controller::fire(true);
}
#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

void autons::auto_blue_flag(bool park) {

  units::Time start_time = pros::millis() * units::MS;

  // get ball from under cap
  intake_controller::set_mode(intake_controller::succ);
  chassis_controller::move_dist_pid(36 * units::INCHES);
  pros::delay(500);

  // shoot flags
  chassis_controller::rotate_pid(-69 * units::DEGREES);
  intake_controller::set_mode(intake_controller::off);
  pros::delay(500);
  catapult_controller::fire();
  pros::delay(250);

  // go to cap
  chassis_controller::rotate_pid(20 * units::DEGREES);
  chassis_controller::move_dist_pid(-30.5 * units::INCHES);
  chassis_controller::rotate_pid(-45 * units::DEGREES);
  chassis_controller::move_dist_pid(6 * units::INCHES);

  // scrape cap
  intake_controller::set_mode(intake_controller::succ);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_SCRAPE);
  chassis_controller::move_dist_pid(-9 * units::INCHES, chassis_controller::dist_pid_constants, false);
  pros::delay(500);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_VERTICAL);
  pros::delay(200);

  // flip cap
  // scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_EXTENDED);
  // chassis_controller::move_dist_pid(-8 * units::INCHES);
  // scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP);
  // chassis_controller::move_dist_pid(6 * units::INCHES);
  // scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_EXTENDED);
  // intake_controller::set_mode(intake_controller::off);

  // get bottom flag
  chassis_controller::rotate_pid(0 * units::DEGREES);
  chassis_controller::move_dist_pid(-6 * units::INCHES);
  chassis_controller::rotate_pid(-90 * units::DEGREES);
  pros::delay(250);
  catapult_controller::fire();
  chassis_controller::move_dist_pid(26 * units::INCHES);
  chassis_controller::rotate_pid(-100 * units::DEGREES);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_SCRAPE, false);
  pros::delay(500);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_INTAKE, false);
  pros::delay(120);

  // double shot own flags
  chassis_controller::rotate_pid(-90 * units::DEGREES);
  chassis_controller::move_dist_pid(-10 * units::INCHES);

}
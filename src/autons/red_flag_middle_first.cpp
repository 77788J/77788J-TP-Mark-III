#include "autons.hpp"
#include "subsystem_controllers/controllers.hpp"

void autons::auto_red_flag_middle_first(bool park) {

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
  chassis_controller::move_dist_pid(-chassis_interface::get_dist_linear());

  // rotate to flags
  chassis_controller::rotate_pid(90 * units::DEGREES);

  // shoot
  intake_controller::set_mode(intake_controller::off);
  catapult_controller::fire(true);

  // go to platform
  chassis_controller::rotate_pid(-30 * units::DEGREES);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);
  chassis_controller::move_dist_pid(18 * units::INCHES);

  // scrape platform
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_FLIP, false);
  intake_controller::set_mode(intake_controller::succ);
  pros::delay(250);
  chassis_controller::move_dist_pid(-16 * units::INCHES);
  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);

  // goto cap
  chassis_controller::rotate_pid(-2 * units::DEGREES);
  chassis_controller::move_dist_pid(44 * units::INCHES);

  // rotate and shoot
  chassis_controller::rotate_pid(83 * units::DEGREES);
  catapult_controller::fire(true);

  

}
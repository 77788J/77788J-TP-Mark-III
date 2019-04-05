#include "main.h"
#include "auton_selector.hpp"
#include "subsystem_controllers/controllers.hpp"


void autonomous() {

  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_VERTICAL, false);

  // try {if (autons::selected != nullptr) autons::selected(autons::park);}
  // catch (...) {}

  // autons::auto_blue_flag(false);
  autons::auto_blue_flag_meta(false);

  // chassis_controller::rotate_pid(90 * units::DEGREES);
  // lift_controller::goto_height(lift_interface::ANGLE_EXTEND, false);

  // while (true) {
  //   printf("ANGLE: %Lf\n", chassis_interface::get_orientation() / units::DEGREES);
  //   pros::delay(10);
  // }

}

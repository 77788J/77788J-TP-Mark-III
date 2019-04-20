#include "main.h"
#include "auton_selector.hpp"
#include "subsystem_controllers/controllers.hpp"


void autonomous() {

  scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_RETRACTED, false);
  lift_controller::goto_angle_custom(lift_interface::ANGLE_MIN, false);

  try {if (autons::selected != nullptr) autons::selected(autons::park);}
  catch (...) {}

}

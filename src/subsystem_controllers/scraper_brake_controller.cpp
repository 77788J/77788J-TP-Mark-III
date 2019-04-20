#include "subsystem_controllers/scraper_brake_controller.hpp"

namespace scraper_controller {


  // currently braking?
  bool is_braked = false;


  // go to angle
  void goto_angle(units::Angle angle, bool wait, units::Angle threshold) {

    // set vars
    // if (angle != scraper_interface::ANGLE_BRAKE_ENGAGED) is_braked = false;

    // move
    scraper_interface::move_position_angular_custom(angle);

    // wait
    if (wait) while (fabs(scraper_interface::get_angle() - angle) > threshold) pros::delay(10);
  }


  // brake
  void brake(bool wait, units::Angle threshold) {
    is_braked = true;
    // goto_angle(scraper_interface::ANGLE_BRAKE_ENGAGED, wait, threshold);
  }
}


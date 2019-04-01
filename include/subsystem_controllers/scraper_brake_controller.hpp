#ifndef SCRAPER_BRAKE_CONTROLLER_H_
#define SCRAPER_BRAKE_CONTROLLER_H_

#include "subsystem_interfaces/scraper_brake_interface.hpp"

namespace scraper_controller {

  static const units::Angle targets[5] = {
    scraper_interface::ANGLE_BRAKE_ENGAGED,
    scraper_interface::ANGLE_SCRAPER_INTAKE,
    scraper_interface::ANGLE_SCRAPER_VERTICAL,
    scraper_interface::ANGLE_SCRAPER_SCRAPE,
    scraper_interface::ANGLE_SCRAPER_FLIP
  };

  // currently braking?
  extern bool is_braked;

  // go to position
  void goto_angle(units::Angle angle, bool wait=true, units::Angle threshold=2*units::DEGREES);

  // brake
  void brake(bool wait=true, units::Angle threshold=2*units::DEGREES);
}

#endif

#ifndef CATAPULT_CONTROLLER_H_
#define CATAPULT_CONTROLLER_H_

#include "subsystem_interfaces/catapult_interface.hpp"

namespace catapult_controller {

  // voltage to be set when in override mode
  extern int override_voltage;
  extern bool is_overriden;
  extern units::Angle slipgear_target;

  // fire catapult
  void fire(bool wait_for_fire=false);

  // set override
  void set_override(bool _override);

  // is catapult at load angle?
  static const inline bool get_at_load_angle(units::Angle tolerance=5*units::DEGREES) 
  { return catapult_interface::get_angle_catapult() >= catapult_interface::ANGLE_CATAPULT_LOAD - tolerance; }

  // wait for catapult to be at load angle
  void wait_for_load_angle(units::Angle tolerance=5*units::DEGREES, units::Time timeout=1*units::MIN);
  

  // update controller
  void update();

}

#endif
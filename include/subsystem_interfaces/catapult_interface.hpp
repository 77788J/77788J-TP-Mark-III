#ifndef CATAPULT_INTERFACE_H_
#define CATAPULT_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic catapult control
namespace catapult_interface {

  // slipgear positions
  static const units::Angle ANGLE_SLIPGEAR_ENGAGE = 0; // angle at which slipgear engages
  static const units::Angle ANGLE_SLIPGEAR_SLIP = 60; // angle at which slipgear slips

  // gear ratios
  static const float REDUCTION_SLIPGEAR = 5; // gear reduction from motor to slipgear
  static const float REDUCTION_CATAPULT = 25.0 / 3.0; // gear reduction from motor to catapult arm

  // get current angle of slipgear
  units::Angle get_angle_slipgear(bool cumulative=false);

  // get current angle of catapult arm
  units::Angle get_angle_catapult();

  // set voltage of catapult
  void move_voltage(int voltage);

  // set position of slipgear with integrated position PID
  void move_position_slipgear(units::Angle position);

}

#endif
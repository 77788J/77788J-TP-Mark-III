#ifndef LIFT_INTERFACE_H_
#define LIFT_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic lift control
namespace lift_interface {

  // gear reduction
  static const float GEAR_REDUCTION = 5;

  // predefined positions
  static const units::Angle ANGLE_MIN = 0 * units::DEGREES;
  static const units::Angle ANGLE_MAX = 180 * units::DEGREES;
  static const units::Angle ANGLE_EXTEND = 45 * units::DEGREES;
  static const units::Angle ANGLE_HOLD_CAP = 20 * units::DEGREES;

  // ports
  static const int PORT = 7;

  // get current angle
  units::Angle get_angle(bool at_motor=false);

  // calculate current height
  units::Distance get_height();

  // get current velocity
  units::AngularVelocity get_velocity(bool at_motor=false);

  // set voltage
  void move_voltage(int voltage);

  // move with integrated position controller
  void move_position_angular(units::Angle angle); // move to angle
  void move_position_linear(units::Distance height); // move to height
}

#endif
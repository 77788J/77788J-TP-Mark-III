#ifndef LIFT_INTERFACE_H_
#define LIFT_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic lift control
namespace lift_interface {

  // physical characteristics
  static const float GEAR_REDUCTION = 5;
  static const units::Distance BAR_LENGTH = 15 * units::INCHES;
  static const units::Distance FULCRUM_HEIGHT = 18 * units::INCHES;

  // predefined positions
  static const units::Angle ANGLE_MIN = -45 * units::DEGREES;
  static const units::Angle ANGLE_MAX = 135 * units::DEGREES;
  static const units::Angle ANGLE_EXTEND = 0 * units::DEGREES;
  static const units::Angle ANGLE_HOLD_CAP = -25 * units::DEGREES;

  // ports
  static const int PORT = 8;

  // motor
  extern pros::Motor motor;

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
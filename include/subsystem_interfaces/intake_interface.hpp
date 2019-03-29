#ifndef INTAKE_INTERFACE_H_
#define INTAKE_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic intake control
namespace intake_interface {

  // ports
  static const int PORT_MOTOR = 6;
  static const char PORT_LIMIT = 'E';

  // motors
  extern pros::Motor motor;

  // sensors
  extern pros::ADIDigitalIn limit_switch;

  // detect of limit switch pressed
  bool get_limit_pressed();

  // get current angle
  units::Angle get_angle();

  // get current velocity (at motor)
  units::AngularVelocity get_velocity();

  // set voltage
  void move_voltage(int voltage);

  // move with integrated velocity controller
  void move_velocity(units::AngularVelocity vel);
}

#endif
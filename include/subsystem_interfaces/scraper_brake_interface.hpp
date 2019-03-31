#ifndef SCRAPER_BRAKE_INTERFACE_H_
#define SCRAPER_BRAKE_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic scraper/brake control
namespace scraper_interface {

  // subsystem selection
  enum Subsystem {subsystem_motor, scraper, brake};

  // physical characteristics
  static const float SCRAPER_REDUCTION = 1;
  static const float BRAKE_REDUCTION = (24.0 / 12.0) * (5.0 / 3.0);
  static const float MOTOR_HEIGHT = 6.875 * units::INCHES;
  static const float SCRAPER_LENGTH = 8 * units::INCHES;
  static const float BRAKE_HEIGHT = 3.5625 * units::INCHES;
  static const float BRAKE_LENGTH = 5.5 * units::INCHES;

  // predefined positions (motor angle)
  static const units::Angle ANGLE_BRAKE_RETRACTED = 0 * units::DEGREES;
  static const units::Angle ANGLE_BRAKE_ENGAGED = 180 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_RETRACTED = 0 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_INTAKE = -15 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_VERTICAL = -45 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_EXTENDED = -135 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_SCRAPE = -160 * units::DEGREES;
  static const units::Angle ANGLE_SCRAPER_FLIP = -180 * units::DEGREES;

  // ports
  static const int PORT = 4;

  // motor
  extern pros::Motor motor;

  // get current angle
  units::Angle get_angle(Subsystem subsystem);

  // calculate current height
  units::Distance get_height(Subsystem subsystem);

  // get current velocity
  units::AngularVelocity get_velocity(Subsystem subsystem);

  // set voltage
  void move_voltage(int voltage);

  // move with integrated position controller
  void move_position_angular(units::Angle angle, Subsystem subsystem=subsystem_motor); // move to angle
  void move_position_linear(units::Distance height, Subsystem subsystem=scraper); // move to height
}
namespace brake_interface = scraper_interface;

#endif
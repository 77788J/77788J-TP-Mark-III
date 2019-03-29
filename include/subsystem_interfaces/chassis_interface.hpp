#ifndef CHASSIS_INTERFACE_H_
#define CHASSIS_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// simple interface for basic chassis control
namespace chassis_interface {

  // side of chassis
  enum Side {none, left, right, both};

  // measurements
  static const units::Distance WHEEL_DIAM = 3.25 * units::INCHES; // tracking wheel diameter
  static const units::Distance WHEEL_DIST_LEFT = 6 * units::INCHES; // horizontal distance of left tracking wheel from center of chassis
  static const units::Distance WHEEL_DIST_RIGHT = 4 * units::INCHES; // horizontal distance of right tracking wheel from center of chassis
  static const units::AngularVelocity MOTOR_VEL_MAX = 600 * units::RPM; // magimum angular velocity of motors
  static const units::LinearVelocity CHASSIS_VEL_MAX = .925647835 * units::IN_PER_SEC; // maximum linear velocity of chassis

  // ports
  static const int PORT_FRONT_LEFT = 1;
  static const int PORT_BACK_LEFT = 2;
  static const int PORT_FRONT_RIGHT = 3;
  static const int PORT_BACK_RIGHT = 4;
  static const char PORT_ENCODER_LEFT_1 = 'B';
  static const char PORT_ENCODER_LEFT_2 = 'C';
  static const char PORT_ENCODER_RIGHT_1 = 'D';
  static const char PORT_ENCODER_RIGHT_2 = 'E';

  // motors
  extern pros::Motor motor_front_left;
  extern pros::Motor motor_back_left;
  extern pros::Motor motor_front_right;
  extern pros::Motor motor_back_right;

  // encoders
  extern pros::ADIEncoder encoder_left;
  extern pros::ADIEncoder encoder_right;

  // get linear distance
  units::Distance get_dist_linear(Side side=both, bool from_reset=true); // returns total linear distance travelled by encoder wheels

  // get angular distance
  units::Angle get_dist_angular(Side side=both, bool from_reset=true); // returns total angular distance travelled by encoder wheels

  // get orientation
  units::Angle get_orientation(bool from_reset=true);

  #define VELOCITY_IMPLEMENTED false
  #if VELOCITY_IMPLEMENTED

  // get linear velocity
  units::LinearVelocity get_vel_linear(Side side=both); // returns current linear velocity of tracking wheel(s) (not scaled for distance from center)

  // get angular velocity
  units::AngularVelocity get_vel_angular(Side side=both); // returns current angular velocity of tracking wheel(s) (not scaled for distance from center)

  #endif

  // reset distance tracking
  void reset_dist_linear(units::Distance dist=0, Side side=both); // resets current tracked distance (linear input)
  void reset_dist_angular(units::Angle angle=0, Side side=both); // resets current tracked distance (angular input)

  // reset orientation tracking
  void reset_orientation(units::Angle angle=0);

  // move with voltage control
  void move_voltage(int voltage, Side side=both);
  void move_voltage(int left, int right);

  // move with integrated position PID
  void move_position_integrated(units::Distance dist, units::AngularVelocity vel=MOTOR_VEL_MAX*units::RPM, Side side=both);
  void move_position_integrated(units::Distance left, units::Distance right, units::AngularVelocity vel=MOTOR_VEL_MAX*units::RPM);

  // move with integrated velocity controller
  void move_velocity_integrated(units::AngularVelocity vel, Side side=both);
  void move_velocity_integrated(units::AngularVelocity left, units::AngularVelocity right);

  // update interface
  void update();
}

#endif
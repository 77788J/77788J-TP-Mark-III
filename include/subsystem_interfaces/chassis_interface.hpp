#ifndef CHASSIS_INTERFACE_H_
#define CHASSIS_INTERFACE_H_

#include "main.h"
#include "units.hpp"

// side of chassis
enum Side {side_none, side_left, side_right, side_both, side};

// simple interface for basic chassis control
namespace chassis_interface {

  // measurements
  static const units::Distance WHEEL_CIRC = 3.25 * units::INCHES; // tracking wheel circumference
  static const units::Distance WHEEL_DIST_LEFT = 6 * units::INCHES; // horizontal distance of left tracking wheel from center of chassis
  static const units::Distance WHEEL_DIST_RIGHT = 4 * units::INCHES; // horizontal distance of right tracking wheel from center of chassis
  static const units::AngularVelocity MOTOR_VEL_MAX = 600 * units::RPM; // magimum angular velocity of motors
  static const units::LinearVelocity CHASSIS_VEL_MAX = .925647835 * units::IN_PER_SEC; // maximum linear velocity of chassis

  // ports
  static const int PORT_FRONT_LEFT = 1;
  static const int PORT_BACK_LEFT = 2;
  static const int PORT_FRONT_RIGHT = 3;
  static const int PORT_BACK_RIGHT = 4;

  // get linear distance
  units::Distance get_dist_linear(Side side=side_both, bool from_reset=true); // returns total linear distance travelled by encoder wheels

  // get angular distance
  units::Angle get_dist_angular(Side side=side_both, bool from_reset=true); // returns total angular distance travelled by encoder wheels

  // reset distance tracking
  void reset_dist_linear(units::Distance dist, Side side=side_both); // resets current tracked distance (linear input)
  void reset_dist_angular(units::Angle dist, Side side=side_both); // resets current tracked distance (angular input)

  // move chassis
  void move_voltage(int voltage, Side side=side_both); // voltage based movement
  void move_voltage(int left, int right); // voltage based movement


  // move with integrated velocity controller
  void move_velocity_integrated(units::AngularVelocity vel, Side side=side_both);
  void move_velocity_integrated(units::AngularVelocity left, units::AngularVelocity right);
}

#endif
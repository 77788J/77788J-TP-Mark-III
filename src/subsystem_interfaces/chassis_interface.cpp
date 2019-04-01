#include "subsystem_interfaces/chassis_interface.hpp"

namespace chassis_interface {

  // scalars
  static const float DISTANCE_SCALAR = WHEEL_DIAM * .5;

  // motors
  pros::Motor motor_front_left(PORT_FRONT_LEFT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_left(PORT_BACK_LEFT, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_front_right(PORT_FRONT_RIGHT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor motor_back_right(PORT_BACK_RIGHT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

  // encoders
  pros::ADIEncoder encoder_left(PORT_ENCODER_LEFT_1, PORT_ENCODER_LEFT_2);
  pros::ADIEncoder encoder_right(PORT_ENCODER_RIGHT_1, PORT_ENCODER_RIGHT_2, true);

  // reference variables
  units::Angle reference_encoder_left = 0;
  units::Angle reference_encoder_right = 0;
  units::Angle reference_orientation = 0;


  // velocity variavles
  units::AngularVelocity vel_left = 0;
  units::AngularVelocity vel_right = 0;
  units::AngularVelocity vel_orient = 0;


  // get linear distance
  units::Distance get_dist_linear(Side side, bool from_reset) {
    return get_dist_angular(side, from_reset) * DISTANCE_SCALAR;
  }


  // get angular distance
  units::Angle get_dist_angular(Side side, bool from_reset) {
    switch (side) {
      case (left): return encoder_left.get_value() * units::DEGREES + reference_encoder_left * from_reset; break;
      case (right): return encoder_right.get_value() * units::DEGREES + reference_encoder_right * from_reset; break;
      case (both): return (get_dist_angular(left, from_reset) + get_dist_angular(right, from_reset)) * .5; break;
      case (none): return 0; break;
    }
  }


  // get orientation
  units::Angle get_orientation(bool from_reset) {
    // return ((get_dist_linear(right, false) / WHEEL_DIST_RIGHT) - (get_dist_linear(left, false) / WHEEL_DIST_LEFT)) * .5 + reference_orientation * from_reset;
    return (get_dist_linear(right, false) - get_dist_linear(left, false)) / WHEEL_DIST + reference_orientation * from_reset;
  }


  // get linear velocity
  units::LinearVelocity get_vel_linear(Side side) {
    return get_vel_angular(side) * DISTANCE_SCALAR;
  }


  // get angular velocity
  units::AngularVelocity get_vel_angular(Side side) {
    switch (side) {
      case (left): return vel_left; break;
      case (right): return vel_right; break;
      case (both): return (vel_left + vel_right) * .5; break;
      case (none): return 0; break;
    }
  }


  // get rotational velocity
  units::AngularVelocity get_vel_orientation() {
    return vel_orient;
  }


  // reset tracking wheel distance (linear)
  void reset_dist_linear(units::Distance dist, Side side) {
    reset_dist_angular(dist / DISTANCE_SCALAR, side);
  }


  // reset tracking wheel distance (angular)
  void reset_dist_angular(units::Angle angle, Side side) {
    switch (side) {
      case (left): reference_encoder_left = angle - get_dist_angular(left, false); break;
      case (right): reference_encoder_right = angle - get_dist_angular(right, false); break;
      case (both): reset_dist_angular(angle, left); reset_dist_angular(angle, right); break;
      case (none): break;
    }
  }


  // reset orientation tracking
  void reset_orientation(units::Angle angle) {
    reference_orientation = angle - get_orientation(false);
  }


  // move with voltage control
  void move_voltage(int voltage, Side side) {
    switch (side) {
      case (left): motor_front_left.move_voltage(voltage); motor_back_left.move_voltage(voltage); break;
      case (right): motor_front_right.move_voltage(voltage); motor_back_right.move_voltage(voltage); break;
      case (both): move_voltage(voltage, left); move_voltage(voltage, right); break;
      case (none): break;
    }
  }
  void move_voltage(int left, int right) {
    move_voltage(left, Side::left);
    move_voltage(right, Side::right);
  }


  // move with integrated position PID
  void move_position_integrated(units::Angle angle, units::AngularVelocity vel, Side side) {
    switch (side) {
      case (left): motor_front_left.move_absolute(angle / units::DEGREES, vel / units::RPM); motor_back_left.move_absolute(angle / units::DEGREES, vel / units::RPM); break;
      case (right): motor_front_right.move_absolute(angle / units::DEGREES, vel / units::RPM); motor_back_right.move_absolute(angle / units::DEGREES, vel / units::RPM); break;
      case (both): move_position_integrated(angle, vel, left); move_position_integrated(angle, vel, right); break;
      case (none): break;
    }
  }
  void move_position_integrated(units::Angle left, units::Angle right, units::AngularVelocity vel) {
    move_position_integrated(left, vel, Side::left);
    move_position_integrated(right, vel, Side::right);
  }


  // move with integrated velocity controller
  void move_velocity_integrated(units::AngularVelocity vel, Side side) {
    switch (side) {
      case (left): motor_front_left.move_velocity(vel / units::RPM); motor_back_left.move_velocity(vel / units::RPM); break;
      case (right): motor_front_right.move_velocity(vel / units::RPM); motor_back_right.move_velocity(vel / units::RPM); break;
      case (both): move_velocity_integrated(vel, left); move_velocity_integrated(vel, right); break;
      case (none): break;
    }
  }
  void move_velocity_integrated(units::AngularVelocity left, units::AngularVelocity right) {
    move_velocity_integrated(left, Side::left);
    move_velocity_integrated(right, Side::right);
  }
  

  // update interface
  units::Time last_update = pros::millis() * units::MS;
  units::Angle last_pos_left = get_dist_angular(left);
  units::Angle last_pos_right = get_dist_angular(right);
  units::Angle last_pos_orientation = get_orientation();
  void update() {

    // calculate velocity
    units::Time elapsed = pros::millis() * units::MS - last_update;
    vel_left = vel_left * .6 + (get_dist_angular(left) - last_pos_left) / elapsed * .4;
    vel_right = vel_right * .6 + (get_dist_angular(right) - last_pos_right) / elapsed * .4;
    vel_orient = vel_orient * .6 + (get_orientation() - last_pos_orientation) / elapsed * .4;

    // set previous values
    last_update = pros::millis() * units::MS;
    last_pos_left = get_dist_angular(left);
    last_pos_right = get_dist_angular(right);
    last_pos_orientation = get_orientation();
  }
}
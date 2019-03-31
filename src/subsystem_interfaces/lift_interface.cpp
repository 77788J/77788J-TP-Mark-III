#include "subsystem_interfaces/lift_interface.hpp"

// simple interface for basic lift control
namespace lift_interface {


  // motor
  pros::Motor motor(PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


  // get current angle
  units::Angle get_angle(bool at_motor) {
    if (at_motor) return motor.get_position() * units::DEGREES / GEAR_REDUCTION + ANGLE_MIN;
    else return motor.get_position() * units::DEGREES;
  }


  // calculate current height
  units::Distance get_height() {
    return sin(get_angle()) * BAR_LENGTH;
  }


  // get current velocity
  units::AngularVelocity get_velocity(bool at_motor) {
    return motor.get_actual_velocity() / GEAR_REDUCTION;
  }


  // set voltage
  void move_voltage(int voltage) {
    motor.move_voltage(voltage);
  }


  // move with integrated position controller
  void move_position_angular(units::Angle angle) {
    motor.move_absolute((angle - ANGLE_MIN) * GEAR_REDUCTION / units::DEGREES, 200);
  }
  void move_position_linear(units::Distance height) {
    units::Angle angle = asin(height / BAR_LENGTH);
    move_position_angular(angle);
  }
}

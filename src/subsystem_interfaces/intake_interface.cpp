#include "subsystem_interfaces/intake_interface.hpp"

// simple interface for basic intake control
namespace intake_interface {


  // motor
  pros::Motor motor(PORT_MOTOR, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);


  // sensors
  pros::ADIDigitalIn limit_switch(PORT_LIMIT);


  // detect of limit switch pressed
  bool get_limit_pressed() {
    return limit_switch.get_value();
  }

  // get current angle
  units::Angle get_angle() {
    return motor.get_position() * units::DEGREES;
  }

  // get current velocity (at motor)
  units::AngularVelocity get_velocity() {
    return motor.get_actual_velocity() * units::RPM;
  }

  // set voltage
  void move_voltage(int voltage) {
    motor.move_voltage(voltage);
  }

  // move with integrated velocity controller
  void move_velocity(units::AngularVelocity vel) {
    motor.move_velocity(vel);
  }
}

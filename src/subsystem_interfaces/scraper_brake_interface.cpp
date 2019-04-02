#include "subsystem_interfaces/scraper_brake_interface.hpp"

// simple interface for basic scraper/brake control
namespace scraper_interface {


  // motor
  pros::Motor motor(PORT, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);


  // get current angle
  units::Angle get_angle(Subsystem subsystem) {
    switch (subsystem) {
      case (subsystem_motor): return motor.get_position() * units::DEGREES; break;
      case (scraper): return motor.get_position() * units::DEGREES + ANGLE_SCRAPER_EXTENDED; break;
      case (brake): return -(motor.get_position() * units::DEGREES + ANGLE_BRAKE_RETRACTED) / BRAKE_REDUCTION; break;
    }
  }


  // calculate current height
  units::Distance get_height(Subsystem subsystem) {
    switch (subsystem) {
      case (subsystem_motor): return MOTOR_HEIGHT; break;
      case (scraper): return MOTOR_HEIGHT + SCRAPER_LENGTH * sin(get_angle(scraper)); break;
      case (brake): return BRAKE_HEIGHT + BRAKE_LENGTH * sin(get_angle(brake)); break;
    }
  }


  // get current velocity
  units::AngularVelocity get_velocity(Subsystem subsystem) {
    switch (subsystem) {
      case (subsystem_motor): return motor.get_actual_velocity() * units::RPM; break;
      case (scraper): return motor.get_actual_velocity() * units::RPM; break;
      case (brake): return -motor.get_actual_velocity() * units::RPM / BRAKE_REDUCTION; break;
    }
  }


  // set voltage
  void move_voltage(int voltage) {
    motor.move_voltage(voltage);
  }


  // move with integrated position controller
  void move_position_angular(units::Angle angle, Subsystem subsystem) {
    switch (subsystem) {
      case (subsystem_motor): motor.move_absolute(angle / units::DEGREES, 200); break;
      case (scraper): motor.move_absolute((angle - ANGLE_SCRAPER_EXTENDED) / units::DEGREES, 200); break;
      case (brake): motor.move_absolute((angle - ANGLE_BRAKE_RETRACTED) * BRAKE_REDUCTION / units::DEGREES, 200); break;
    }
  }
  void move_position_linear(units::Distance height, Subsystem subsystem) {
    switch (subsystem) {
      case (subsystem_motor): break;
      case (scraper): move_position_angular(asin((height - MOTOR_HEIGHT) / SCRAPER_LENGTH), scraper);
      case (brake): move_position_angular(asin((height - BRAKE_HEIGHT) / BRAKE_LENGTH), brake);
    }
  }
}

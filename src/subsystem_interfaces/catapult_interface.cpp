#include "subsystem_interfaces\catapult_interface.hpp"

namespace catapult_interface {

  // motors
  pros::Motor motor(PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);


  // get current angle of slipgear
  units::Angle get_angle_slipgear(bool cumulative) {
    return cumulative ? motor.get_position() / REDUCTION_SLIPGEAR : fmod(motor.get_position() / REDUCTION_SLIPGEAR, 120 * units::DEGREES);
  }


  // get current angle of catapult arm
  units::Angle get_angle_catapult() {
    units::Angle angle_slipgear = get_angle_slipgear();
    units::Angle angle_change = (angle_slipgear >= ANGLE_SLIPGEAR_ENGAGE && angle_slipgear <= ANGLE_SLIPGEAR_SLIP) * angle_slipgear;
    return ANGLE_CATAPULT_RELEASE * units::DEGREES - angle_change;
  }


  // set voltage of catapult
  void move_voltage(int voltage) {
    motor.move_voltage(voltage);
  }

  // set position of slipgear with integrated position PID
  void move_position_slipgear(units::Angle position) {
    motor.move_absolute(position * REDUCTION_SLIPGEAR / units::DEGREES, 100);
  }
}

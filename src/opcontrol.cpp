#include "main.h"
#include "subsystem_interfaces/chassis_interface.hpp"
#include "lib/joystick.hpp"

void opcontrol() {
  pros::lcd::initialize();
  Joystick controller;

  while (true) {
    controller.update();
    // printf("left: %f\tright: %f\n", chassis_interface::get_dist_linear(chassis_interface::left), chassis_interface::get_dist_linear(chassis_interface::right));
    printf("%Lf\n", chassis_interface::get_orientation() / units::DEGREES);
	  pros::lcd::print(1, "left: %f\tright: %f\n", chassis_interface::get_dist_linear(chassis_interface::left), chassis_interface::get_dist_linear(chassis_interface::right));
	  pros::lcd::print(2, "%Lf\n", chassis_interface::get_orientation() / units::DEGREES);

    chassis_interface::move_voltage(controller.analog_left_y * 12000, controller.analog_right_y * 12000);

    pros::delay(20);
  }
}

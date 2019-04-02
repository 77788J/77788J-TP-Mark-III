#include "main.h"
#include "subsystem_interfaces/interfaces.hpp"
#include "subsystem_controllers/controllers.hpp"
#include "lib/joystick.hpp"

void opcontrol() {
  Joystick controller;

  interfaces::initialize();

  while (true) {

    // update controllers
    controller.update();

    // TODO put these in own task
    chassis_interface::update();
    catapult_controller::update();
    intake_controller::update();

    // drive
    chassis_interface::move_voltage(controller.analog_left_y * 12000, controller.analog_right_y * 12000);

    // catapult
    if (controller.btn_r1_new == 1) catapult_controller::fire();
    if (controller.btn_x_new == 1) {
      catapult_controller::override_voltage = 0;
      catapult_controller::set_override(true);
    }
    if (controller.btn_x_new == -1) catapult_controller::set_override(false);

    // intake
    if (controller.btn_r2) intake_controller::set_mode(intake_controller::succ);
    else if (controller.btn_a) intake_controller::set_mode(intake_controller::spit);
    else intake_controller::set_mode(intake_controller::automatic);

    // lift
    if (controller.btn_up) {
      for (int i = 0; i < 3; i++) {
        if (lift_interface::get_angle() < lift_controller::lift_targets[i] - 8 * units::DEGREES) {
          lift_controller::goto_angle(lift_controller::lift_targets[i], false);
          break;
        }
      }
    }
    if (controller.btn_down) {
      for (int i = 3; i  >= 0; i--) {
        if (lift_interface::get_angle() > lift_controller::lift_targets[i] + 8 * units::DEGREES) {
          lift_controller::goto_angle(lift_controller::lift_targets[i], false);
          break;
        }
      }
    }

    // scraper/brake
    if (controller.btn_l1 && controller.btn_l2) scraper_controller::brake(false);
    else {
      if (scraper_controller::is_braked) scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_INTAKE, false);
      if (controller.btn_l1) {
        for (int i = 0; i < 5; ++i) {
          if (scraper_interface::get_angle() < scraper_controller::targets[i] - 6 * units::DEGREES) {
            scraper_controller::goto_angle(scraper_controller::targets[i], false);
            break;
          }
        }
      }
      if (controller.btn_l2) {
        for (int i = 4; i >= 0; --i) {
          if (scraper_interface::get_angle() > scraper_controller::targets[i] + 6 * units::DEGREES) {
            scraper_controller::goto_angle(scraper_controller::targets[i], false);
            break;
          }
        }
      }
    }

    printf("lift angle: %Lf\tscraper angle: %Lf\n", lift_interface::get_angle(), scraper_interface::get_angle());

    pros::delay(10);
  }
}

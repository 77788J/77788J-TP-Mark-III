#include "main.h"
#include "macros.hpp"
#include "subsystem_interfaces/interfaces.hpp"
#include "subsystem_controllers/controllers.hpp"
#include "lib/joystick.hpp"

bool auto_intake_enabled = true;

void opcontrol() {
  Joystick controller;

  interfaces::initialize();
  controller.controller.set_text(0, 0, intake_controller::enable_automatic ? "AUTO ENABLED" : "AUTO DISABLED");

  while (true) {

    // update controller
    controller.update();

    // drive
    if (controllers::chassis_mutex.take(0)) {
      chassis_interface::move_voltage(controller.analog_left_y * 12000, controller.analog_right_y * 12000);
      controllers::chassis_mutex.give();
    }

    // catapult
    if (controllers::catapult_mutex.take(0)) {
      if (controller.btn_r1_new == 1) catapult_controller::fire();
      if (controller.btn_x_new == 1) {
        catapult_controller::override_voltage = 0;
        catapult_controller::set_override(true);
      }
      if (controller.btn_x_new == -1) catapult_controller::set_override(false);
      if (controller.btn_y_new == 1) macros::set_macro(macros::macro_calibrate_slipgear);
      controllers::catapult_mutex.give();
    }

    // intake
    if (controllers::intake_mutex.take(0)) {
      // if (controller.btn_y_new == 1) {
      //   intake_controller::enable_automatic = !intake_controller::enable_automatic;
      //   controller.controller.set_text(0, 0, intake_controller::enable_automatic ? "AUTO ENABLED" : "AUTO DISABLED");
      // }
      if (controller.btn_r2) intake_controller::set_mode(intake_controller::succ);
      else if (controller.btn_a) intake_controller::set_mode(intake_controller::spit);
      else intake_controller::set_mode(intake_controller::automatic);
      controllers::intake_mutex.give();
    }

    // lift
    if (controllers::lift_mutex.take(0)) {
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
      controllers::lift_mutex.give();
    }

    // scraper/brake
    if (controllers::scraper_mutex.take(0)) {
      if (controller.btn_l1 && controller.btn_l2) scraper_controller::brake(false);
      else {
        if (scraper_controller::is_braked) scraper_controller::goto_angle(scraper_interface::ANGLE_SCRAPER_INTAKE, false);
        if (controller.btn_l2) {
          for (int i = 0; i < 4; ++i) {
            if (scraper_interface::get_angle() > scraper_controller::targets[i] + 6 * units::DEGREES) {
              scraper_controller::goto_angle(scraper_controller::targets[i], false);
              break;
            }
          }
        }
        if (controller.btn_l1) {
          for (int i = 3; i >= 0; --i) {
            if (scraper_interface::get_angle() < scraper_controller::targets[i] - 6 * units::DEGREES) {
              scraper_controller::goto_angle(scraper_controller::targets[i], false);
              break;
            }
          }
        }
      }
      controllers::scraper_mutex.give();
    }

    pros::delay(10);
  }
}

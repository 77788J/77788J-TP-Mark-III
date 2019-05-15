#include "main.h"
#include "macros.hpp"
#include "subsystem_interfaces/interfaces.hpp"
#include "subsystem_controllers/controllers.hpp"
#include "lib/joystick.hpp"

bool auto_intake_enabled = true;
bool chassis_braked = false;

void opcontrol() {
  Joystick controller;

  controller.controller.set_text(0, 0, intake_controller::enable_automatic ? "AUTO ENABLED" : "AUTO DISABLED");

  while (true) {
    
    chassis_controller::mode = chassis_controller::none;

    // update controller
    controller.update();

    // drive
    if (!chassis_braked && controllers::chassis_mutex.take(0)) {
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
      controllers::catapult_mutex.give();
    }

    // intake
    if (controllers::intake_mutex.take(0)) {
      if (controller.btn_left_new == 1) {
        intake_controller::enable_automatic = !intake_controller::enable_automatic;
        controller.controller.set_text(0, 0, intake_controller::enable_automatic ? "AUTO ENABLED" : "AUTO DISABLED");
      }
      if (controller.btn_r2) intake_controller::set_mode(intake_controller::succ);
      else if (controller.btn_y) intake_controller::set_mode(intake_controller::spit);
      else intake_controller::set_mode(intake_controller::automatic);
      controllers::intake_mutex.give();
    }

    // lift
    if (controllers::lift_mutex.take(0)) {
      if (controller.btn_up) {
        for (int i = 0; i < 3; i++) {
          if (lift_interface::get_angle() < lift_controller::lift_targets[i] - 8 * units::DEGREES) {
            lift_controller::goto_angle_custom(lift_controller::lift_targets[i], false);
            break;
          }
        }
      }
      if (controller.btn_down) {
        for (int i = 3; i  >= 0; i--) {
          if (lift_interface::get_angle() > lift_controller::lift_targets[i] + 8 * units::DEGREES) {
            lift_controller::goto_angle_custom(lift_controller::lift_targets[i], false);
            break;
          }
        }
      }
      controllers::lift_mutex.give();
    }

    // scraper/brake
    if (controllers::scraper_mutex.take(0)) {
      if (controller.btn_right) {
        scraper_controller::brake(false);
        if (!chassis_braked && controllers::chassis_mutex.take(0)) {
          chassis_braked = true;
          chassis_interface::motor_front_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
          chassis_interface::motor_back_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
          chassis_interface::motor_front_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
          chassis_interface::motor_back_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
          chassis_interface::move_velocity_integrated(0);
          controllers::chassis_mutex.give();
        }
      }
      else {
        if (controllers::chassis_mutex.take(0)) {
          chassis_braked = false;
          chassis_interface::motor_front_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
          chassis_interface::motor_back_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
          chassis_interface::motor_front_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
          chassis_interface::motor_back_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
          controllers::chassis_mutex.give();
        }
        if (controller.btn_l1_new == 1) scraper_interface::move_position_angular_custom(scraper_interface::ANGLE_SCRAPER_VERTICAL);
        if (controller.btn_l1_new == -1) scraper_interface::move_position_angular_custom(scraper_interface::ANGLE_SCRAPER_RETRACTED);
        if (controller.btn_l2_new == 1) scraper_interface::move_position_angular_custom(scraper_interface::ANGLE_SCRAPER_FLIP);
      }
      controllers::scraper_mutex.give();
    }

    pros::delay(10);
    // scraper_interface::move_voltage(0);
    printf("angle: %Lf\n", scraper_interface::get_angle() / units::DEGREES);
  }
}

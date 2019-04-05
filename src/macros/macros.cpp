#include "macros.hpp"

namespace macros {

  // task
  pros::Task* task = nullptr;


  // current macro
  Macro current = macro_init;


  // update macros
  void update(void* params) {
    while (true) {
      switch (current) {

        case (macro_none): break;
        case (macro_init): break;
        case (macro_calibrate_slipgear): calibrate_slipgear(); break;

      }

      current = macro_none;
      pros::delay(10);
    }
  }


  // set current macro
  void set_macro(Macro macro) {

    printf("CALIBRATE");

    // restart task if current running macro
    if (current != macro_none) {
      if (task != nullptr) task->remove();
      task = new pros::Task(update);
    }

    // set current macro
    current = macro;
  }


  // calibrate slipgear
  void calibrate_slipgear() {

    // take control of catapult
    controllers::catapult_mutex.take(40);
    
    // override catapult voltage
    catapult_controller::override_voltage = 2000;
    catapult_controller::set_override(true);

    // wait for velocity to catch up
    pros::delay(750);

    // wait for velocity to be 0
    while (catapult_interface::motor.get_actual_velocity() > 1) pros::delay(10);

    // turn off motor
    catapult_controller::override_voltage = 0;

    // wait briefly for catapult to stabilize
    pros::delay(500);

    // give up control of catapult
    catapult_controller::set_override(false);
    controllers::catapult_mutex.give();

  }

}
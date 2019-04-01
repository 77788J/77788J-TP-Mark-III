#include "subsystem_controllers/intake_controller.hpp"

namespace intake_controller {

  // vision sensor
  pros::Vision vision(PORT_VISION);


  // intake mode
  IntakeMode mode = automatic;


  // rules
  int max_balls_in_posession = 2;
  int max_balls_loaded = 1;


  // set mode
  void set_mode(IntakeMode m) {
    mode = m;
    switch (m) {
      case (automatic): break;
      case (succ): intake_interface::move_voltage(12000); break;
      case (spit): intake_interface::move_voltage(-12000);  break;
      case(off): intake_interface::move_voltage(0); break;
      case (hold): intake_interface::move_velocity(0); break;
    }
  }
 

  // update
  float limit_pressed = false;
  units::Time time_since_intake = 1000 * units::MS;
  void update() {

    // see if a ball is touching the limit switch
    float limit_now = limit_pressed;
    if (intake_interface::get_limit_pressed()) {
      limit_now = true;
      time_since_intake = 0;
    }
    else limit_now = limit_now * .8;

    // see if a ball has just left the limit switch
    if (limit_pressed && !limit_now) {
      if (intake_interface::motor.get_voltage() > 0) ++balls_loaded;
      else --balls_in_possession;
      ball_in_intake = false;
    }
    if (!limit_pressed && limit_now) {
      ++balls_in_possession;
      ball_in_intake = true;
    }

    // auto intake
    if (mode == automatic) {

      // check if ball is present
      bool ball = false;
      if (vision.get_object_count() > 0) {
        pros::vision_object_s_t b = vision.get_by_sig(0, 0);
        if (b.top_coord < VISION_THRESHOLD) {
          ball = true;
          time_since_intake = 0;
        }
      }

      // set intake
      if (ball_in_intake && (balls_loaded >= max_balls_loaded)) intake_interface::move_velocity(0);
      else if ((ball && balls_in_possession < max_balls_in_posession) || (ball_in_intake && balls_loaded < max_balls_loaded))
        intake_interface::move_voltage(12000);
      else if (time_since_intake <= 1000 * units::MS) intake_interface::move_voltage(12000);
      else intake_interface::move_voltage(0);

      time_since_intake += 10;
    }
  }
}

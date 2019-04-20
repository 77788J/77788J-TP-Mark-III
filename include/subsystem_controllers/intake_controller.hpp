#ifndef INTAKE_CONTROLLER_H_
#define INTAKE_CONTROLLER_H_

#include "subsystem_interfaces/intake_interface.hpp"

namespace intake_controller {

  // vision sensor
  static const int PORT_VISION = 12;
  static const int VISION_THRESHOLD = 35;
  extern pros::Vision vision;

  // intake mode
  enum IntakeMode {automatic, succ, spit, off, hold};
  extern IntakeMode mode;
  extern bool enable_automatic;

  // rules
  extern int max_balls_in_posession;
  extern int max_balls_loaded;

  // ball states
  extern int balls_in_possession;
  extern int balls_loaded;
  extern bool ball_in_intake;

  // set mode
  void set_mode(IntakeMode m);

  // update
  void update();

}

#endif

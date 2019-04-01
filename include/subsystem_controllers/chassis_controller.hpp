#ifndef CHASSIS_CONTROLLER_H_
#define CHASSIS_CONTROLLER_H_

#include "subsystem_interfaces/chassis_interface.hpp"

namespace chassis_controller {

  typedef struct PidConstants {
    float kp; // proportional constant
    float ki; // integral constant
    float kd; // derivative constant
    float max_accel; // maximum acceleration (vel difference per 10ms)
  } PidConstants;

  // move distance with custom PID controller
  void move_dist_pid(units::Distance dist, PidConstants constants, bool wait=true, bool* flag=nullptr);

  // rotate with custom PID controller
  void rotate_pid(units::Angle orientation, PidConstants constants, bool wait=true, bool* flag=nullptr);

}

#endif
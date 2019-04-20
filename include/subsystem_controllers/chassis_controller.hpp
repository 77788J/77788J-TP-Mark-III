#ifndef CHASSIS_CONTROLLER_H_
#define CHASSIS_CONTROLLER_H_

#include "subsystem_interfaces/chassis_interface.hpp"

namespace chassis_controller {

  enum MovementMode {
      none,
      dist_pid,
      rot_pid
    };
  extern MovementMode mode;

  typedef struct PidConstants {
    float kp; // proportional constant
    float ki; // integral constant
    float kd; // derivative constant
    float max_accel; // maximum acceleration (vel difference per 10ms)
    int min_voltage; // minimum voltage to supply
  } PidConstants;

  // constants
  extern PidConstants dist_pid_constants;
  extern PidConstants orientation_pid_constants;

  // move distance with custom PID controller
  void move_dist_pid(units::Distance dist, PidConstants constants=dist_pid_constants, bool wait=true, bool* flag=nullptr);

  // move dist (PID) (with timeout)
  void move_dist_pid(units::Distance dist, units::Time timeout, bool* flag=nullptr);

  // rotate with custom PID controller
  void rotate_pid(units::Angle orientation, PidConstants constants=orientation_pid_constants, bool wait=true, bool* flag=nullptr);

  // update controller
  void update();

}

#endif
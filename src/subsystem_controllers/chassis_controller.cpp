#include "subsystem_controllers/chassis_controller.hpp"

namespace chassis_controller {

  // movement modes
  enum MovementMode {
    none,
    dist_pid,
    rot_pid
  };
  MovementMode mode = none;


  // async move dist (PID)
  float move_pid_target = 0;
  PidConstants move_pid_constants;
  float move_pid_integral = 0;
  int move_pid_prev_voltage = 0;
  bool* move_pid_flag = nullptr;
  void move_dist_pid_async(units::Distance target, PidConstants constants, bool* flag=nullptr) {

    // calculate error
    float error = target - chassis_interface::get_dist_linear();

    // calculate P
    float p = error * constants.kp;

    // calculate I
    if (fabs(error) <= 12 * units::FEET) move_pid_integral += error;
    float i = move_pid_integral *  constants.ki;

    // calculate D
    float d = chassis_interface::get_vel_linear() * constants.kd;

    // calculate PID and account for max accel
    float pid = p + i + d;
    if (pid - move_pid_prev_voltage > constants.max_accel) pid = move_pid_prev_voltage + constants.max_accel;
    if (move_pid_prev_voltage - pid > constants.max_accel) pid = move_pid_prev_voltage - constants.max_accel;
    
    // acount for min voltage
    if (fabs(pid) > 500 && fabs(pid) < constants.min_voltage) pid = pid > 0 ? constants.min_voltage : -constants.min_voltage;

    // set motors
    chassis_interface::move_voltage(pid);
    move_pid_prev_voltage = pid;

    // break
    if (fabs(error) < .25 * units::INCHES || (fabs(error) < .5 * units::INCHES && fabs(pid) < 1000))  *flag = true;
  }


  // move distance PID
  PidConstants dist_pid_constants = {
    .kp = 1,
    .ki = 1,
    .kd = 1,
    .max_accel = 1000,
    .min_voltage = 4000
  };
  void move_dist_pid(units::Distance dist, PidConstants constants, bool wait, bool* flag) {

    // set vals
    mode = dist_pid;
    move_pid_target = dist + chassis_interface::get_dist_linear();
    move_pid_constants = dist_pid_constants;
    move_pid_integral = 0;
    move_pid_prev_voltage = 0;

    // setup flag
    if (flag != nullptr) move_pid_flag = flag;
    *move_pid_flag = false;

    // wait if applicable
    if (wait) while (!*move_pid_flag) pros::delay(10);
  }


  // async rotate (PID)
  float rotate_pid_target = 0;
  PidConstants rotate_pid_constants;
  float rotate_pid_integral = 0;
  int rotate_pid_prev_voltage = 0;
  bool* rotate_pid_flag = nullptr;
  void rotate_pid_async(units::Angle target, PidConstants constants, bool* flag=nullptr) {

    // calculate error
    float error = target - chassis_interface::get_orientation();

    // calculate P
    float p = error * constants.kp;

    // calculate I
    if (fabs(error) <= 12 * units::FEET) rotate_pid_integral += error;
    float i = rotate_pid_integral *  constants.ki;

    // calculate D
    float d = chassis_interface::get_vel_orientation() * constants.kd;

    // calculate PID and account for max accel
    float pid = p + i + d;
    if (pid - rotate_pid_prev_voltage > constants.max_accel) pid = rotate_pid_prev_voltage + constants.max_accel;
    if (rotate_pid_prev_voltage - pid > constants.max_accel) pid = rotate_pid_prev_voltage - constants.max_accel;
    
    // acount for min voltage
    if (fabs(pid) > 500 && fabs(pid) < constants.min_voltage) pid = pid > 0 ? constants.min_voltage : -constants.min_voltage;

    // set motors
    chassis_interface::move_voltage(-pid, pid);
    rotate_pid_prev_voltage = pid;

    // break
    if (fabs(error) < .25 * units::INCHES || (fabs(error) < .5 * units::INCHES && fabs(pid) < 1000))  *flag = true;
  }


  // rotate PID
  PidConstants orientation_pid_constants = {
    .kp = 1,
    .ki = 1,
    .kd = 1,
    .max_accel = 1000,
    .min_voltage = 4000
  };
  void rotate_pid(units::Angle orientation, PidConstants constants, bool wait, bool* flag) {

    // set vals
    mode = rot_pid;
    rotate_pid_target = orientation;
    rotate_pid_constants = orientation_pid_constants;
    rotate_pid_integral = 0;
    rotate_pid_prev_voltage = 0;

    // setup flag
    if (flag != nullptr) move_pid_flag = flag;
    *rotate_pid_flag = false;

    // wait if applicable
    if (wait) while (!*move_pid_flag) pros::delay(10);
  }


  // update controller
  void update() {
    switch (mode) {

      case (none): break;
      case (dist_pid): move_dist_pid_async(move_pid_target, move_pid_constants, move_pid_flag); break;
      case (rot_pid): rotate_pid_async(rotate_pid_target, rotate_pid_constants, rotate_pid_flag); break;
    }
  }
}

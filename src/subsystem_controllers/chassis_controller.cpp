#include "subsystem_controllers/chassis_controller.hpp"

namespace chassis_controller {

  // movement modes
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
    if (fabs(error) <= 4 * units::INCHES) move_pid_integral += error;
    float i = move_pid_integral *  constants.ki;

    // calculate D
    float d = chassis_interface::get_vel_linear() * constants.kd;

    // calculate PID and account for max accel
    float pid = p + i + d;
    if (pid - move_pid_prev_voltage > constants.max_accel) pid = move_pid_prev_voltage + constants.max_accel;
    if (move_pid_prev_voltage - pid > constants.max_accel) pid = move_pid_prev_voltage - constants.max_accel;
    
    // acount for max voltage
    if (fabs(pid) > constants.max_voltage) pid = pid > 0 ? constants.max_voltage : -constants.max_voltage;

    // set motors
    chassis_interface::move_voltage(pid);
    move_pid_prev_voltage = pid;

    // break
    if (fabs(chassis_interface::get_vel_linear()) <= 3 * units::INCHES / units::SEC && fabs(error) < .6 * units::INCHES) *flag = true;
    // if (fabs(error) < .25 * units::INCHES || (fabs(error) < .5 * units::INCHES && fabs(pid) < 1000)) *flag = true;
  }


  // move distance PID
  PidConstants dist_pid_constants = {
    .kp = 1450,
    .ki = 10,
    .kd = -150000,
    .max_accel = 910,
    .max_voltage = 12000,
    .min_voltage = 2500
  };
  void move_dist_pid(units::Distance dist, PidConstants constants, bool wait, bool* flag) {

    // set vals
    mode = dist_pid;
    move_pid_target = dist + chassis_interface::get_dist_linear();
    move_pid_constants = constants;
    move_pid_integral = 0;
    move_pid_prev_voltage = 0;

    // setup flag
    if (flag == nullptr) move_pid_flag = new bool;
    else move_pid_flag = flag;
    *move_pid_flag = false;

    // wait if applicable
    if (wait) while (!*move_pid_flag) pros::delay(10);
    chassis_interface::move_velocity_integrated(0 * units::RPM);
  }


  // move dist (PID) (with timeout)
  void move_dist_pid(units::Distance dist, units::Time timeout, bool* flag) {

    // start movement
    move_dist_pid(dist, dist_pid_constants, false, flag);

    // wait
    units::Time t = pros::millis() * units::MS;
    while (pros::millis() * units::MS - t < timeout && !*move_pid_flag) pros::delay(10);
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
    if (fabs(error) <= 20 * units::DEGREES) rotate_pid_integral += error;
    float i = rotate_pid_integral *  constants.ki;

    // calculate D
    float d = chassis_interface::get_vel_orientation() * constants.kd;

    // calculate PID and account for max accel
    float pid = p + i + d;
    if (pid - rotate_pid_prev_voltage > constants.max_accel) pid = rotate_pid_prev_voltage + constants.max_accel;
    if (rotate_pid_prev_voltage - pid > constants.max_accel) pid = rotate_pid_prev_voltage - constants.max_accel;
    
    // acount for max voltage
    if (fabs(pid) > constants.max_voltage) pid = pid > 0 ? constants.max_voltage : -constants.max_voltage;

    // set motors
    chassis_interface::move_voltage(-pid, pid);
    rotate_pid_prev_voltage = pid;

    // break
    // if (fabs(error) < 1.25 * units::DEGREES || (fabs(error) < 2.5 * units::DEGREES && fabs(pid) < 1000))  *flag = true;
    if (fabs(chassis_interface::get_vel_orientation()) <= 20 * units::DEGREES / units::SEC && fabs(error) < 10 * units::DEGREES) *flag = true;
  }


  // rotate PID
  PidConstants orientation_pid_constants = {
    .kp = 10750,
    .ki = 20,
    .kd = -132,
    .max_accel = 1000,
    .max_voltage = 12000,
    .min_voltage = 2500
  };
  void rotate_pid(units::Angle orientation, PidConstants constants, bool wait, bool* flag) {

    // set vals
    mode = rot_pid;
    rotate_pid_target = orientation;
    rotate_pid_constants = constants;
    rotate_pid_integral = 0;
    rotate_pid_prev_voltage = 0;

    // setup flag
    if (flag == nullptr) rotate_pid_flag = new bool;
    else rotate_pid_flag = flag;
    *rotate_pid_flag = false;

    // wait if applicable
    if (wait) while (!*rotate_pid_flag) pros::delay(10);
    // pros::delay(250);
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

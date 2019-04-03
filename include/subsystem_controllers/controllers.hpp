#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "catapult_controller.hpp"
#include "chassis_controller.hpp"
#include "intake_controller.hpp"
#include "lift_controller.hpp"
#include "scraper_brake_controller.hpp"

namespace controllers {

  // task
  extern pros::Task* task;
  
  // mutexes
  extern pros::Mutex catapult_mutex;
  extern pros::Mutex chassis_mutex;
  extern pros::Mutex intake_mutex;
  extern pros::Mutex lift_mutex;
  extern pros::Mutex scraper_mutex;

  // initializer
  void initialize();

  // update function
  void update(void* params);

}

#endif
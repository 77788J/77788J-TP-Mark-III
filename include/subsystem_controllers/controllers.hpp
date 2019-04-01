#ifndef CONTROLLERS_H_
#define CONTROLLERS_H_

#include "catapult_controller.hpp"
#include "chassis_controller.hpp"
#include "intake_controller.hpp"
#include "lift_controller.hpp"
#include "scraper_brake_controller.hpp"

namespace controllers {

  extern pros::Task task;

  void initialize();

  void update(void* params);

}

#endif
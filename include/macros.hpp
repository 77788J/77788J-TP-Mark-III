#ifndef MACROS_H_
#define MACROS_H_

#include "main.h"
#include "subsystem_controllers/controllers.hpp"

namespace macros {

  // task
  extern pros::Task* task;

  // current macro
  enum Macro {macro_none, macro_calibrate_slipgear};
  extern Macro current;

  // update macros
  void update(void* params);

  // set current macro
  void set_macro(Macro macro);

  // macros
  void calibrate_slipgear();

}

#endif
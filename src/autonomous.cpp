#include "main.h"
#include "auton_selector.hpp"

void autonomous() {
  try {if (autons::selected != nullptr) autons::selected(autons::park);}
  catch (...) {}
}

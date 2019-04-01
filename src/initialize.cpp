#include "main.h"
#include "subsystem_controllers/controllers.hpp"
#include "auton_selector.hpp"

void initialize() {
  controllers::initialize();
  auton_selector::create_display();
}

void disabled() {}

void competition_initialize() {}

#include "subsystem_controllers/controllers.hpp"

namespace controllers {

  // create update task
  pros::Task* task = nullptr;


  // initialize al subsystem controllers
  void initialize() {
    *task = pros::Task(update);
  }


  // update all subsystem controllers
  void update(void* params) {
    while (true) {
    
      chassis_controller::update();

      pros::delay(10);

    }
  }
}
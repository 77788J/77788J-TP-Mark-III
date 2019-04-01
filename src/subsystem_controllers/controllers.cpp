#include "subsystem_controllers/controllers.hpp"

namespace controllers {

  // create update task
  pros::Task task(update);


  // initialize al subsystem controllers
  void initialize() {}


  // update all subsystem controllers
  void update(void* params) {
    while (true) {
    
      chassis_controller::update();

      pros::delay(10);

    }
  }
}
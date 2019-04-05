#include "subsystem_controllers/controllers.hpp"
#include "macros.hpp"

namespace controllers {

  // create update task
  pros::Task* task = nullptr;

  
  // mutexes
  pros::Mutex catapult_mutex;
  pros::Mutex chassis_mutex;
  pros::Mutex intake_mutex;
  pros::Mutex lift_mutex;
  pros::Mutex scraper_mutex;


  // initialize al subsystem controllers
  void initialize() {
    task = new pros::Task(update);
    macros::task = new pros::Task(macros::update);
    macros::set_macro(macros::macro_none);
  }


  // update all subsystem interfaces and controllers
  void update(void* params) {
    while (true) {
    
      if (chassis_mutex.take(0)) {
        chassis_interface::update();
        chassis_controller::update();
        chassis_mutex.give();
      }
      if (catapult_mutex.take(0)) {
        catapult_controller::update();
        catapult_mutex.give();
      }
      if (intake_mutex.take(0)) {
        intake_controller::update();
        intake_mutex.give();
      }

      pros::delay(10);
    }
  }
}
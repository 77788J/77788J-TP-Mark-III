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
    
        chassis_interface::update();
        chassis_controller::update();

        catapult_controller::update();

        scraper_interface::update();

        lift_controller::update();

        intake_controller::update();

      pros::delay(10);
    }
  }
}
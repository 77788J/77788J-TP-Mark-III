#ifndef AUTON_SELECTOR_H_
#define AUTON_SELECTOR_H_

#include "main.h"
#include "autons.hpp"

namespace auton_selector {

  // main function, creates all objects
  void create_display();

  // styles
  extern lv_style_t style_button_red;
  extern lv_style_t style_button_red_pressed;
  extern lv_style_t style_button_blue;
  extern lv_style_t style_button_blue_pressed;
  extern lv_style_t style_button_neutral;
  extern lv_style_t style_button_neutral_pressed;
  void styles_init();

}

#endif
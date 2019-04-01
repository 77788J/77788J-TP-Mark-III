#include "../../include/auton_selector.hpp"

namespace auton_selector {

  // declarations
  lv_style_t style_button_red;
  lv_style_t style_button_red_pressed;
  lv_style_t style_button_blue;
  lv_style_t style_button_blue_pressed;
  lv_style_t style_button_neutral;
  lv_style_t style_button_neutral_pressed;


  // initialize styles
  void styles_init() {
    lv_style_copy(&style_button_blue, &lv_style_plain);
    lv_style_copy(&style_button_neutral, &lv_style_plain);


    // red button (not pressed)
    lv_style_copy(&style_button_red, &lv_style_plain);
    style_button_red.body.main_color = LV_COLOR_MAKE(255, 0, 0);
    style_button_red.body.grad_color = LV_COLOR_MAKE(255, 0, 0);
    style_button_red.body.radius = 8;
    style_button_red.body.border.color = LV_COLOR_MAKE(200, 0, 0);
    style_button_red.body.border.width = 2;

    // red button (pressed)
    lv_style_copy(&style_button_red_pressed, &style_button_red);
    style_button_red_pressed.body.main_color = LV_COLOR_MAKE(200, 0, 0);
    style_button_red_pressed.body.grad_color = LV_COLOR_MAKE(200, 0, 0);


    // blue button (not pressed)
    lv_style_copy(&style_button_blue, &lv_style_plain);
    style_button_blue.body.main_color = LV_COLOR_MAKE(0, 0, 255);
    style_button_blue.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
    style_button_blue.body.radius = 8;
    style_button_blue.body.border.color = LV_COLOR_MAKE(0, 0, 200);
    style_button_blue.body.border.width = 2;

    // blue button (pressed)
    lv_style_copy(&style_button_blue_pressed, &style_button_blue);
    style_button_blue_pressed.body.main_color = LV_COLOR_MAKE(0, 0, 200);
    style_button_blue_pressed.body.grad_color = LV_COLOR_MAKE(0, 0, 200);


    // neutral button (not pressed)
    lv_style_copy(&style_button_neutral, &lv_style_plain);
    style_button_neutral.body.main_color = LV_COLOR_MAKE(200, 200, 200);
    style_button_neutral.body.grad_color = LV_COLOR_MAKE(200, 200, 200);
    style_button_neutral.body.radius = 8;
    style_button_neutral.body.border.color = LV_COLOR_MAKE(169, 169, 169);
    style_button_neutral.body.border.width = 2;

    // blue button (pressed)
    lv_style_copy(&style_button_neutral_pressed, &style_button_neutral);
    style_button_neutral_pressed.body.main_color = LV_COLOR_MAKE(169, 169, 169);
    style_button_neutral_pressed.body.grad_color = LV_COLOR_MAKE(169, 169, 169);

  }
}
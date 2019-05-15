#include "auton_selector.hpp"
#include "subsystem_controllers/chassis_controller.hpp"

namespace auton_selector {


  // declare buttons
  lv_obj_t* btn_red_flag;
  lv_obj_t* btn_red_cap;
  lv_obj_t* btn_blue_flag;
  lv_obj_t* btn_blue_cap;
  lv_obj_t* btn_no_auton;


  // callbacks
  // lv_res_t btn_click_action_red_flag(lv_obj_t * btn) {autons::selected = autons::auto_red_flag; chassis_interface::reset_orientation(); return LV_RES_OK;}
  lv_res_t btn_click_action_red_flag(lv_obj_t * btn) {autons::selected = autons::auto_red_3_flag; chassis_interface::reset_orientation(); return LV_RES_OK;}
  lv_res_t btn_click_action_red_cap(lv_obj_t * btn) {autons::selected = autons::auto_red_cap; chassis_interface::reset_orientation(); return LV_RES_OK;}
  lv_res_t btn_click_action_blue_flag(lv_obj_t * btn) {autons::selected = autons::auto_blue_3_flag; chassis_interface::reset_orientation(180 * units::DEGREES); return LV_RES_OK;}
  lv_res_t btn_click_action_blue_cap(lv_obj_t * btn) {autons::selected = autons::auto_blue_cap; chassis_interface::reset_orientation(180 * units::DEGREES); return LV_RES_OK;}
  lv_res_t btn_click_action_no_auton(lv_obj_t * btn) {autons::selected = nullptr; chassis_interface::reset_orientation(); return LV_RES_OK;}


  // create all display objects
  void create_display() {

    // initialize styles
    styles_init();

    // create red flag button
    lv_obj_t* btn_red_flag = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_red_flag, 16, 16);
    lv_obj_set_size(btn_red_flag, 96, 96);
    lv_btn_set_style(btn_red_flag, LV_BTN_STYLE_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_flag, LV_BTN_STYLE_REL, &style_button_red);
    lv_btn_set_style(btn_red_flag, LV_BTN_STYLE_TGL_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_flag, LV_BTN_STYLE_TGL_REL, &style_button_red);
    lv_btn_set_action(btn_red_flag, LV_BTN_ACTION_PR, btn_click_action_red_flag);

    // create red cap button
    lv_obj_t* btn_red_cap = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_red_cap, 16, 128);
    lv_obj_set_size(btn_red_cap, 96, 96);
    lv_btn_set_style(btn_red_cap, LV_BTN_STYLE_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_cap, LV_BTN_STYLE_REL, &style_button_red);
    lv_btn_set_style(btn_red_cap, LV_BTN_STYLE_TGL_PR, &style_button_red_pressed);
    lv_btn_set_style(btn_red_cap, LV_BTN_STYLE_TGL_REL, &style_button_red);
    lv_btn_set_action(btn_red_cap, LV_BTN_ACTION_PR, btn_click_action_red_cap);

    // create blue flag button
    lv_obj_t* btn_blue_flag = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_blue_flag, 128, 16);
    lv_obj_set_size(btn_blue_flag, 96, 96);
    lv_btn_set_style(btn_blue_flag, LV_BTN_STYLE_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_flag, LV_BTN_STYLE_REL, &style_button_blue);
    lv_btn_set_style(btn_blue_flag, LV_BTN_STYLE_TGL_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_flag, LV_BTN_STYLE_TGL_REL, &style_button_blue);
    lv_btn_set_action(btn_blue_flag, LV_BTN_ACTION_PR, btn_click_action_blue_flag);

    // create blue cap button
    lv_obj_t* btn_blue_cap = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_blue_cap, 128, 128);
    lv_obj_set_size(btn_blue_cap, 96, 96);
    lv_btn_set_style(btn_blue_cap, LV_BTN_STYLE_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_cap, LV_BTN_STYLE_REL, &style_button_blue);
    lv_btn_set_style(btn_blue_cap, LV_BTN_STYLE_TGL_PR, &style_button_blue_pressed);
    lv_btn_set_style(btn_blue_cap, LV_BTN_STYLE_TGL_REL, &style_button_blue);
    lv_btn_set_action(btn_blue_cap, LV_BTN_ACTION_PR, btn_click_action_blue_cap);

    // create no auton button
    lv_obj_t* btn_no_auton = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn_no_auton, 256, 16);
    lv_obj_set_size(btn_no_auton, 208, 72);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_PR, &style_button_neutral_pressed);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_REL, &style_button_neutral);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_TGL_PR, &style_button_neutral_pressed);
    lv_btn_set_style(btn_no_auton, LV_BTN_STYLE_TGL_REL, &style_button_neutral);
    lv_btn_set_action(btn_no_auton, LV_BTN_ACTION_PR, btn_click_action_no_auton);

  }
}
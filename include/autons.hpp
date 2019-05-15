#ifndef AUTONS_H_
#define AUTONS_H_

#include "units.hpp"

namespace autons {

  // variables
  extern void (*selected)(bool);
  extern bool park;
  extern units::Angle angle_start;

  // functions
  void auto_red_flag(bool park);
  void auto_red_flag_middle_first(bool park);
  void auto_red_3_flag(bool park);
  void auto_blue_flag(bool park);
  void auto_blue_3_flag(bool park);
  void auto_red_cap(bool park);
  void auto_blue_cap(bool park);

}

#endif
#ifndef AUTONS_H_
#define AUTONS_H_

namespace autons {

  // variables
  extern void (*selected)(bool);
  extern bool park;

  // functions
  void auto_red_flag(bool park);
  void auto_blue_flag(bool park);
  void auto_red_cap(bool park);
  void auto_blue_cap(bool park);

}

#endif
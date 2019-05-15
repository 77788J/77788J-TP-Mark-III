#include "../../include/autons.hpp"

namespace autons {

  void (*selected)(bool) = nullptr;
  units::Angle angle_start = 0 * units::DEGREES;
  bool park = false;
  
}
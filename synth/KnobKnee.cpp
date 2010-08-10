#include "KnobKnee.h"

KnobKnee::KnobKnee(uint16_t range, uint8_t kneeX, uint16_t kneeY) {
  this->range = range;
  this->kneeX = kneeX;
  this->kneeY = kneeY;
}


uint16_t KnobKnee::getValue(uint8_t midiValue) {
  uint16_t out;

  if (midiValue <= kneeX) {
    out = ((uint16_t)kneeY*(uint16_t)midiValue)/kneeX;
  }
  else {
    out = ((uint16_t)(range-kneeY)*(uint16_t)(midiValue-kneeX))/(127-kneeX)+kneeY;
  }

  return out;
}


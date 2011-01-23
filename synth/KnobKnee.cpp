#include "KnobKnee.h"

KnobKnee::KnobKnee(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2, uint16_t maxValue) {
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->maxValue = maxValue;
}


uint16_t KnobKnee::getValue(uint8_t midiValue) {
  uint32_t out;

  if (midiValue <= x1) {
    out = (uint32_t)y1 * (uint32_t)midiValue;
    out /= x1;
  } else if (midiValue <= x2) {
    out = (uint32_t)(y2 - y1) * (uint32_t)(midiValue - x1);
    out /= (x2 - x1);
    out += y1;
  } else {
    out = (uint32_t)(maxValue - y2) * (uint32_t)(midiValue - x2);
    out /= (127 - x2);
    out += y2;
  }

  return (uint16_t)out;
}


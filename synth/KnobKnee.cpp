#include "KnobKnee.h"

KnobKnee::KnobKnee(uint8_t x1, uint16_t y1, uint8_t x2, uint16_t y2, uint16_t maxValue) {
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->maxValue = maxValue;
}


uint16_t KnobKnee::getValue(uint8_t midiValue) {
  uint16_t out;

  if (midiValue <= x1) {
    return (y1*(uint16_t)midiValue)/x1;
  } else if (midiValue <= x2) {
    return ((y2-y1)*(uint16_t)(midiValue-x1+1))/(x2-x1) + y1;
  } else {
    return ((maxValue-y2)*(uint16_t)(midiValue-x2+1))/(127-x2) + y1;
  }

}


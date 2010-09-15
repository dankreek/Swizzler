/*
 * LinearIncrementor.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: justin
 */

#include "LinearIncrementor.h"

LinearIncrementor::LinearIncrementor() {}

void LinearIncrementor::start(uint16_t startValue, uint16_t endValue, uint16_t numSteps, uint8_t resolution) {
  //resolution = (resolution > 16) ? 16 : resolution;
  startValue = startValue << (16-resolution);
  endValue = endValue << (16-resolution);

  incAmount = ((int16_t)endValue - (int16_t)startValue)/(int16_t)numSteps;

  this->resolution = resolution;
  this->endVal = endValue;
  curVal = startValue;
  this->numSteps = numSteps;
}

uint16_t LinearIncrementor::next() {
  stepNum++;
  curVal += incAmount;

  if (stepNum >= numSteps) curVal = endVal;

  // Return the value in it's true resolution
  return ((curVal >> (16-resolution)));
}

bool LinearIncrementor::stillGoing() {
  return (curVal != endVal);
}

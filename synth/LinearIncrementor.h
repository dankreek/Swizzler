/*
 * LinearIncrementor.h
 *
 *  Created on: Aug 1, 2010
 *      Author: justin
 *
 *  Incrementing a value linearly over a period of time seems to be something
 *  I'm doing a lot so I'm just making one class to handle it. You essentially
 *  start a LinearIncrementor by providing it a start value, an ending value
 *  and the number of increments. You then call the next function and it will
 *  return the next value in the series. The internal mechanics of this class
 *  compute everything in 16 bit resolution, but the actual input/output
 *  resolution is specified by the user.
 */

#ifndef LINEARINCREMENTOR_H_
#define LINEARINCREMENTOR_H_

#include <inttypes.h>

class LinearIncrementor {
public:
  LinearIncrementor();

  /**
   * Start the linear increment trip
   *
   * @startValue        The beginning value for the linear trip
   * @endValue          The ending value for the trip
   * @numSteps          The number of steps in the trip
   * @resolution        The resolution of the numbers in the trip (in bits)
   */
  void start(uint16_t startValue, uint16_t endValue, uint16_t numSteps, uint8_t resolution);

  /**
   * Get the next value in the series and put it in val.
   *
   */
  uint16_t next();

  // Is the incremental series still running?
  bool stillGoing();
private:
  uint16_t endVal;
  int16_t incAmount;
  uint16_t curVal;
  uint8_t resolution;
  uint16_t numSteps;
  uint16_t stepNum;
};

#endif /* LINEARINCREMENTOR_H_ */

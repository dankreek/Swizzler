/*
 * INoteReceiver.h
 *
 *  Created on: Aug 16, 2010
 *      Author: justin
 *
 *  Interface defining a class which can receive note events
 */

#ifndef ANOTERECEIVER_H_
#define ANOTERECEIVER_H_

#include <inttypes.h>

class ANoteReceiver {
public:
  virtual void noteOn(uint8_t noteNumber, uint8_t velocity) = 0;
  virtual void noteOff(uint8_t noteNumber) = 0;

  /**
   * This note receiver should recalculate all of its data
   */
  virtual void update() = 0;
};

#endif /* ANOTERECEIVER_H_ */

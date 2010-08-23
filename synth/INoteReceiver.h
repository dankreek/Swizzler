/*
 * INoteReceiver.h
 *
 *  Created on: Aug 16, 2010
 *      Author: justin
 *
 *  Interface defining a class which can receive note events
 */

#ifndef INOTERECEIVER_H_
#define INOTERECEIVER_H_

#include <inttypes.h>

class INoteReceiver {
public:
  virtual void noteOn(uint8_t noteNumber, uint8_t velocity) = 0;
  virtual void noteOff(uint8_t noteNumber) = 0;
};

#endif /* INOTERECEIVER_H_ */

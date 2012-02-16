/** @file ANoteReceiver.h
 *
 *  Created on: Aug 16, 2010
 *      Author: justin
 *
 *  Interface defining a class which can receive note events
 */

#ifndef ANOTERECEIVER_H_
#define ANOTERECEIVER_H_

#include <inttypes.h>

/**
 * Abstract class defining the behaviour of class which receives MIDI notes.
 *
 * @see ANoteTransmitter
 */
class ANoteReceiver {
public:
  /**
   * Recieve a "note on" command
   *
   * @param noteNumber  MIDI note number to recieve
   * @param velocity    Velocity of the note
   */
  virtual void noteOn(uint8_t noteNumber, uint8_t velocity) = 0;

  /**
   * Recieve a "note off" command
   *
   * @param noteNumber  MIDI note number to be turned off
   */
  virtual void noteOff(uint8_t noteNumber) = 0;

  /**
   * This note receiver should recalculate all of its data
   */
  virtual void update() = 0;
};

#endif /* ANOTERECEIVER_H_ */

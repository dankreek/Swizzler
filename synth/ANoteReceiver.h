/** @file   ANoteReceiver.h
 *  @date   Aug 16, 2010
 *  @author Justin May <may.justin@gmail.com>
 *
 *  Interface defining a class which can receive note events
 */

#ifndef ANOTERECEIVER_H_
#define ANOTERECEIVER_H_

#include <inttypes.h>

/**
 * Abstract class defining the behavior of class which receives MIDI notes.
 *
 * @see ANoteTransmitter
 */
class ANoteReceiver {
public:
  /**
   * Receive a "note on" command
   *
   * @param noteNumber  MIDI note number to receive
   * @param velocity    Velocity of the note
   */
  virtual void noteOn(uint8_t noteNumber, uint8_t velocity) = 0;

  /**
   * Receive a "note off" command
   *
   * @param noteNumber  MIDI note number to be turned off
   */
  virtual void noteOff(uint8_t noteNumber) = 0;

  /**
   * This note receiver needs to recalculate all of its data
   */
  virtual void update() = 0;

protected:
  ~ANoteReceiver();
};

inline ANoteReceiver::~ANoteReceiver() {}

#endif /* ANOTERECEIVER_H_ */

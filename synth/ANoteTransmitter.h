/*
 * INoteTransmitter.h
 *
 *  Created on: Aug 22, 2010
 *      Author: justin
 *
 * This interface provides the note sending functionality. A reference
 * to
 */

#ifndef INOTETRANSMITTER_H_
#define INOTETRANSMITTER_H_

#include <inttypes.h>
#include "ANoteReceiver.h"

class ANoteTransmitter {
public:
  // Hook the note receiver up to the output
  void linkTo(ANoteReceiver *recv);

  // The ANoteTansmitter interface allows a class to send a note to a note receiver
  void sendNoteOn(uint8_t noteNumber, uint8_t velocity);
  void sendNoteOff(uint8_t noteNumber);
protected:
  // Reference to the class which receives the note
  ANoteReceiver *receiver;
};

inline
void ANoteTransmitter::linkTo(ANoteReceiver *recv) {
  receiver = recv;
}

inline
void ANoteTransmitter::sendNoteOn(uint8_t noteNumber, uint8_t velocity) {
  receiver->noteOn(noteNumber, velocity);
}

inline
void ANoteTransmitter::sendNoteOff(uint8_t noteNumber) {
  receiver->noteOff(noteNumber);
}

#endif /* INOTETRANSMITTER_H_ */

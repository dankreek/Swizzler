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
  void linkTo(ANoteReceiver *recv);

  // The ANoteTansmitter interface allows a class to send a note to a note receiver
  void sendNote(uint8_t noteNumber, uint8_t velocity);
protected:
  // Reference to the class which receives the note
  ANoteReceiver *receiver;
};

inline
void ANoteTransmitter::sendNote(uint8_t noteNumber, uint8_t velocity) {
  receiver->noteOn(noteNumber, velocity);
}

#endif /* INOTETRANSMITTER_H_ */

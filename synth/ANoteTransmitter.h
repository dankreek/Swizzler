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
#include "INoteReceiver.h"

class ANoteTransmitter {
public:
  ANoteTransmitter(INoteReceiver *recv);

  // The INoteTansmitter interface allows a class to send a note to a note receiver
  virtual void sendNote(uint8_t noteNumber, uint8_t velocity) = 0;
private:
  // Reference to the class which receives the note
  INoteReceiver *receiver;
};

#endif /* INOTETRANSMITTER_H_ */

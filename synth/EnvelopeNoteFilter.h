/*
 * EnvelopeNoteFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef ENVELOPENOTEFILTER_H_
#define ENVELOPENOTEFILTER_H_

#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"

class EnvelopeNoteFilter : public ANoteReceiver, public ANoteTransmitter {
public:
  EnvelopeNoteFilter();
  virtual void noteOn(uint8_t noteNumber, uint8_t velocity);
  virtual void noteOff(uint8_t noteNumber);
private:
  // Current note number being played (or -1 if none being played)
  int8_t curNoteNum;

  // Restart the sound chip gate
  void restartGate();
};

#endif /* ENVELOPENOTEFILTER_H_ */

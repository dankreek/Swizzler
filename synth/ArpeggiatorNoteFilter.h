/*
 * ArpeggiatorNoteFilter.h
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#ifndef ARPEGGIATORNOTEFILTER_H_
#define ARPEGGIATORNOTEFILTER_H_

#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"

class ArpeggiatorNoteFilter : public ANoteReceiver, public ANoteTransmitter {
public:

  void noteOn(uint8_t noteNumber, uint8_t velocity);
  void noteOff(uint8_t noteNumber);

};

#endif /* ARPEGGIATORNOTEFILTER_H_ */

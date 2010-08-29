/*
 * DirectNoteFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef DIRECTNOTEFREQFILTER_H_
#define DIRECTNOTEFREQFILTER_H_

#include "ANoteReceiver.h"
#include "AFreqTransmitter.h"

class DirectNoteFreqFilter : public ANoteReceiver, public AFreqTransmitter {
public:
  DirectNoteFreqFilter();
  void noteOn(uint8_t noteNumber, uint8_t velocity);
  void noteOff(uint8_t noteNumber);

};

#endif /* DIRECTNOTEFREQFILTER_H_ */

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
#include "MidiNoteBuffer.h"
#include "ITimerCall.h"
#include <inttypes.h>

class ArpeggiatorNoteFilter : public ANoteReceiver, public ANoteTransmitter, ITimerCall {
public:
  ArpeggiatorNoteFilter();

  void noteOn(uint8_t noteNumber, uint8_t velocity);
  void noteOff(uint8_t noteNumber);

  uint8_t getMinNotes() const;
  void setMinNotes(uint8_t);

  void setArpTime(uint16_t);

  void nextTick();

private:
  uint16_t curTime;
  uint8_t  minNotes;

  // Amount of time (in ms) that each note should be played
  uint16_t arpTime;

  // Current note being played's buffer index
  uint8_t curNoteI;

  MidiNoteBuffer noteBuffer;
};

#endif /* ARPEGGIATORNOTEFILTER_H_ */

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

  enum ArpeggioDirection {
    forward  = 0x00,
    backward = 0x01,
    random   = 0x02
  };

  void setArpDirection(ArpeggioDirection dir);

  uint8_t getMinNotes() const;
  void setMinNotes(uint8_t);


  void setArpTime(uint16_t);

  void nextTick();

private:
  ArpeggioDirection curDir;
  uint16_t          curTime;    // Time elapsed during
  uint8_t           minNotes;

  // Amount of time (in ms) that each note should be played
  uint16_t arpTime;

  // Current note being played's noteBuffer index
  int8_t nextNoteI;

  MidiNoteBuffer noteBuffer;

  void restartArpeggio();
  void incNextI();
};

#endif /* ARPEGGIATORNOTEFILTER_H_ */

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

class ArpeggiatorNoteFilter : public ANoteReceiver, public ANoteTransmitter, public ITimerCall {
public:
  ArpeggiatorNoteFilter();
  void noteOn(uint8_t noteNumber, uint8_t velocity);
  void noteOff(uint8_t noteNumber);

  /// Different directions that the arpeggio can travel in
  enum ArpeggioDirection { up = 0x00, down = 0x01, random = 0x02 };

  void setArpDirection(ArpeggioDirection dir);

  /**
   *
   */
  uint8_t getMinNotes() const;
  void setMinNotes(uint8_t);

  /**
   * Set the amount of time to wait before switching to the next arpeggio note.
   *
   * @param arpTime Amount of time in number of ticks
   */
  void setArpTime(uint16_t arpTime);

  /// Service routine called by the timer loop
  void nextTick();

  /**
   * Turn the arepggiator on/off
   *
   * @param onOff Set true to bypass the arpeggiator, or false to enable the arpeggiator
   */
  void setBypass(bool onOff);

  void update();

private:
  ArpeggioDirection curDir;
  uint16_t          curTime;    // Time elapsed during
  uint8_t           minNotes;

  /// Is the arpeggiator still on?
  bool isBypassOn;

  /// Amount of time (in ms) that each note should be played
  uint16_t arpTime;

  /// Current note being played's noteBuffer index
  int8_t nextNoteI;

  /// Ordered buffer that keeps track of all the notes being held down
  MidiNoteBuffer noteBuffer;

  void restartArpeggio();

  /// Advance nextNoteI to the next note in the sequence (depending upon direction)
  void incNextI();
};

#endif /* ARPEGGIATORNOTEFILTER_H_ */

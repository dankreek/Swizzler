/** @file   ArpeggiatorNoteFilter.h
 *  @date   Aug 23, 2010
 *  @author Justin May <may.justin@gmail.com>
 */

#ifndef ARPEGGIATORNOTEFILTER_H_
#define ARPEGGIATORNOTEFILTER_H_

#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"
#include "MidiNoteBuffer.h"
#include "ITimerCall.h"
#include <inttypes.h>

/**
 * The arpeggio effect. The user holds down a number of keys and the synthesizer
 * will individually iterate between them in the specified order.
 */ 
class ArpeggiatorNoteFilter : public ANoteReceiver, public ANoteTransmitter, public ITimerCall {
public:
  /**
   * Set some reasonable defaults for the arpeggiator
   */
  ArpeggiatorNoteFilter();

  void noteOn(uint8_t noteNumber, uint8_t velocity);
  void noteOff(uint8_t noteNumber);

  /// Different directions that the arpeggio can travel in
  enum ArpeggioDirection { up = 0, down = 1, random = 2 };

  /**
   * Set the direction in which the arpeggio will be iterated through
   * 
   * @param dir     Arepggio direction
   */
  void setArpDirection(ArpeggioDirection dir);

  /**
   * Get the mininum number of keys that are held down to trigger an arpeggio 
   *
   * @return The miniumum number of notes 
   */
  uint8_t getMinNotes() const;

  /**
   * Set the mininum number of keys the user needs to have held down to create an arpeggio
   * 
   * @param minimumNumberOfNotes    The minimum number of notes
   */ 
  void setMinNotes(uint8_t minimumNumberOfNotes);

  /**
   * Set the amount of time (in ms) between notes in the arpeggio
   *
   * @param arpeggioTime    Time between arpeggio notes (in ms)
   */  
  void setArpTime(uint16_t arpeggioTime);

  /// Service routine called by the timer loop
  void nextTick();

  /**
   * Turn the arepggiator on/off
   *
   * @param onOff   Set true to bypass the arpeggiator, or false to enable the arpeggiator
   */
  void setBypass(bool onOff);

  /// Not used for the arpeggiator
  void update();

private:
  /// Current arpeggio direction
  ArpeggioDirection curDir;
 
  /// Time that has elapsed since the current note in the arpeggio was started
  uint16_t curTime;

  /// The minimum number of notes the user 
  uint8_t minNotes;

  /// Is the arpeggiator still on?
  bool isBypassOn;

  /// Amount of time (in ms) that each note should be played
  uint16_t arpTime;

  /// Current note being played's noteBuffer index
  int8_t nextNoteI;

  /// Ordered buffer that keeps track of all the notes being held down
  MidiNoteBuffer noteBuffer;

  /// Restart the arpeggio from the beginning
  void restartArpeggio();

  /// Advance nextNoteI to the next note in the sequence (depending upon direction)
  void incNextI();
};

#endif /* ARPEGGIATORNOTEFILTER_H_ */

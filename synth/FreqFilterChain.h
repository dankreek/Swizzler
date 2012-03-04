/** @file FreqFilterChain.h
 *  @date Aug 28, 2010
 */

#ifndef FREQFILTERCHAIN_H_
#define FREQFILTERCHAIN_H_

#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"
#include "PitchbendFreqFilter.h"
#include "PortamentoFreqFilter.h"
#include "ITimerCall.h"
#include "FreqModFreqFilter.h"
#include "OutputFreqFilter.h"

/**
 * This class is a container for list of frequency modulations filters. When a <tt>note on</tt>
 * command is received
 *
 * @author Justin May <may.justin@gmail.com>
 */
class FreqFilterChain : public ANoteReceiver, public ANoteTransmitter, public ITimerCall {
public:
  FreqFilterChain();

  /**
   * Receives a note from the MIDI note filter chain and forces an update through
   * the frequency filter chain.
   *
   * @param noteNumber	MIDI note number
   * @param velocity	Velocity that the MIDI key was struck at
   * @see update()
   */
  void noteOn( uint8_t noteNumber, uint8_t velocity );
  void noteOff(uint8_t);

  /**
   * Tell all the frequency modulation effects to calculate the final frequency offset. The oscillators
   * will then be notified that they will need to recalculate their frequencies.
   */
  void update();

  /// The previous note number that was received
  int8_t prevNoteNum;

  /// The current note number being played
  int8_t curNoteNum;

  /// Service all timer functions of each filter
  void nextTick();

  /**
   * Turn portamento on/off
   *
   * @param onOff  If true, turn portamento on, otherwise turn it off
   */
  void setPortamento(bool onOff);

  /**
   * Turn frequency modulation on/off
   *
   * @param onOff	If true, turn the frequency modulation effect on, otherwise turn it off
   */
  void setFrequencyModulation(bool onOff);

  /**
   * @return The current frequency offset (in schlips)
   */
  int16_t getFreqOffset();
private:

  // TODO - I don't think this is needed anymore
  int8_t noteOffset;

  /// Pointer to the first frequency filter in the chain
  AFreqOffsetTransmitter *chainHead;

  // These are all the filters in the chain
  PitchbendFreqFilter pitchbendFilter;          // Calculated pitch bends
  PortamentoFreqFilter portamentoFilter;
  FreqModFreqFilter freqModFilter;              // Frequency modulation filter

  // TODO - Is this needed?
  OutputFreqFilter outputFilter;
};

inline
int16_t FreqFilterChain::getFreqOffset() {
  return outputFilter.curOffset;
}

#endif /* FREQFILTERCHAIN_H_ */

/** @file PortamentoFreqFilter.h
 *  @date Aug 29, 2010
 */

#ifndef PORTAMENTOFREQFILTER_H_
#define PORTAMENTOFREQFILTER_H_

#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"
#include "ITimerCall.h"

/**
 * Frequency filter chain member used to calculate glides between notes when portamento is turned on.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class PortamentoFreqFilter : public AFreqOffsetTransmitter, public AFreqFilterChainMember, public ITimerCall {
// TODO : This thing is buggy as hell! There are problems when turning on and off the portamentoFreqFilter
public:
  PortamentoFreqFilter();

  void updateOffset();

  /**
   *  Reset the Portamento generator to its initial state
   */
  void reset();

  void nextTick();

private:
  /**
   * Number of extra bits of resolution used for calculating the glide between notes.
   * The extra bits are used to maintain precision. The methods _getEffectiveOffset()
   * and _getEffectivePortTime() will return the actual values
   */
  static const uint8_t LINEAR_RESOLUTION = 2;

  /**
   * Send the current frequency offset for the glide to the next filter in the chain
   */
  void _sendEffectiveOffset();

  /**
   * Has a new note been struck since the last frequency update?
   *
   * @return True if a new note has been struck
   */
  bool _isNewNoteStruck();

  /**
   * Check to see if a previous note has been struck since the synth was turned on or since
   * the last call to reset()
   *
   * @return True if a previous
   */
  bool _hasPrevNoteBeenStruck();

  /**
   * Start calculating a new glide using the current _srcPortNote and _destPortNote
   */
  void _startNewGlide();


  /// Keeps track of the number of ticks that have passed while calculating a glide
  uint16_t      _timerCount;

  /**
   * Right-shifts the current frequency offset by the number of bits in LINEAR_RESOLUTION.
   * This operation yields the actual frequency offset.
   *
   * @return The current frequency offset in schlips
   */
  int16_t  _getEffectiveOffset();

  /**
   * Converts Swizzler::portamentoTime from milliseconds to ticks
   *
   * @return Length of the glide measured in number of ticks
   */
  uint16_t _getEffectivePortTime();

  /// Current frequency offset with extra LINEAR_RESOLUTION bits
  int16_t _curSchlipsOffset;

  /// Number of schlips (w/LINEAR_RESOLUTION bits added) to change _curSchlipsOffset by each timer tick
  int16_t _offsetIncAmount;

  // Source and destination portamento note numbers. These are used to tell when a new note has been struck
  // and how fast to change frequencies

  /// The MIDI note number that the glide is going to end up on
  int8_t  _destPortNote;

  /// The MIDI note number that the glide started at
  int8_t  _srcPortNote;
};

inline
int16_t PortamentoFreqFilter::_getEffectiveOffset() {
  return ( _curSchlipsOffset >> LINEAR_RESOLUTION );
}

#endif /* PORTAMENTOFREQFILTER_H_ */

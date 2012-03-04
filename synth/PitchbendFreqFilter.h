/** @file PitchbendFreqFilter.h
 *  @date Aug 29, 2010
 */

#ifndef PITCHBENDFREQFILTER_H_
#define PITCHBENDFREQFILTER_H_

#include "AFreqOffsetReceiver.h"
#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"

/**
 * Member of the frequency filter chain that modulates the output frequency based on the
 * position of the pitch bend wheel. MidiInput::pitchbendAmount and Swizzler::bendRange are
 * used to calculate the modulation amount.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class PitchbendFreqFilter : public AFreqOffsetReceiver, public AFreqOffsetTransmitter, public AFreqFilterChainMember {
public:
  void recvOffset(int16_t);
  void updateOffset();
private:
  /// The last offset that was received by the last filter in the chain.
  int16_t lastOffset;
};

#endif /* PITCHBENDFREQFILTER_H_ */

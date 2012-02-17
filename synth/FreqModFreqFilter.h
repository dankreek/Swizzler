/** @file FreqModFreqFilter.h
 *  @date Oct 3, 2010
 */

#ifndef FREQMODFREQFILTER_H_
#define FREQMODFREQFILTER_H_

#include "AFreqOffsetReceiver.h"
#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"
#include "ITimerCall.h"

/**
 * Frequency modulation effect. The swizzler's sine wave generator and the value of the modulation wheel
 * is used to calculate the frequency offset.
 *
 * @author Justin May <may.justin@gmail.com>
 * @see Swizzler::modWheelLevel
 * @see Swizzler::lfoController
 */
class FreqModFreqFilter : public AFreqOffsetReceiver, public AFreqOffsetTransmitter, public AFreqFilterChainMember {
public:
  FreqModFreqFilter();

  void recvOffset(int16_t offset);
  void updateOffset();

private:
  /// Use the sine generator to calculate the current offset
  int16_t calcCurOffset();

  /// Most recently received offset from previous effect in the chain
  int16_t curBaseOffset;
};

#endif /* FREQMODFREQFILTER_H_ */

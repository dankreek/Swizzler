/** @file OutputFreqFilter.h
 *  @date Jan 16, 2011
 */

#ifndef OUTPUTFREQFILTER_H_
#define OUTPUTFREQFILTER_H_

#include "AFreqOffsetReceiver.h"

/**
 * This is the last filter in the frequency filter chain. It's used to store the
 * final output of the chain, which is then used to modulate the oscillator frequencies.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class OutputFreqFilter : public AFreqOffsetReceiver {
public:
  OutputFreqFilter();

  void recvOffset(int16_t);

  // The last frequency offset (in schlips) received
  int16_t curOffset;
};

#endif /* OUTPUTFREQFILTER_H_ */

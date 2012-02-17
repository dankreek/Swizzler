/** @file   AFreqOffsetReceiver.h
 *  @date   Aug 28, 2010
 *  @author Justin May <may.justin@gmail.com>
 */

#ifndef AFREQRECEIVER_H_
#define AFREQRECEIVER_H_

#include <inttypes.h>

/**
 * Class that contains abstract functionality for an effect that resides in the FrequencyFilterChain which
 * receives a frequency offset from the previous effects in the chain.
 *
 * @author Justin May <may.justin@gmail.com>
 * @see FreqFilterChain
 */
class AFreqOffsetReceiver {
public:
  /**
   * Receive the previous frequency modulation effect's frequency offset (in schlips).
   *
   * The value received actually represents the cumulative offset of all the previous effects in the chain.
   *
   * @param frequencyOffset Sum of all previous frequency offsets 
   */
  virtual void recvOffset(int16_t frequencyOffset) = 0;

protected:
  ~AFreqOffsetReceiver();
};

// This is makes the compiler shut up. No destructors get called in this environment
inline AFreqOffsetReceiver::~AFreqOffsetReceiver() {}

#endif /* AFREQRECEIVER_H_ */

/** @file AFreqReceiver.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef AFREQRECEIVER_H_
#define AFREQRECEIVER_H_

#include <inttypes.h>

/**
 * Class that contains abstract functionality for an effect that resides in the FrequencyFilterChain which
 * recieves a frequency offset from the previous effects in the chain.
 *
 * @see FreqFilterChain
 */
class AFreqOffsetReceiver {
public:
  /**
   * Recieve the previous frequency modulation effect's frequency offset (in schlips). 
   *
   * The value recieved actually reperesents the cumulitive offset of all the previous effects in the chain.
   *
   * @param frequencyOffset Sum of all previous frequency offsets 
   */
  virtual void recvOffset(int16_t frequencyOffset) = 0;
};

#endif /* AFREQRECEIVER_H_ */

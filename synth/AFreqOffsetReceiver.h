/*
 * AFreqReceiver.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef AFREQRECEIVER_H_
#define AFREQRECEIVER_H_

#include <inttypes.h>

class AFreqOffsetReceiver {
public:
  virtual void recvOffset(int16_t freq) = 0;
};

#endif /* AFREQRECEIVER_H_ */

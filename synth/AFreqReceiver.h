/*
 * AFreqReceiver.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 */

#ifndef AFREQRECEIVER_H_
#define AFREQRECEIVER_H_

#include <inttypes.h>

class AFreqReceiver {
public:
  virtual void recvFreq(uint16_t freq) = 0;
};

#endif /* AFREQRECEIVER_H_ */

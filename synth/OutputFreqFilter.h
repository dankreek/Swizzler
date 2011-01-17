/*
 * OutputFreqFilter.h
 *
 *  Created on: Jan 16, 2011
 *      Author: justin
 */

#ifndef OUTPUTFREQFILTER_H_
#define OUTPUTFREQFILTER_H_

#include "AFreqOffsetReceiver.h"

class OutputFreqFilter : public AFreqOffsetReceiver {
public:
  OutputFreqFilter();

  void recvOffset(int16_t);

  // The last schlips offset calculated
  int16_t curOffset;
};

#endif /* OUTPUTFREQFILTER_H_ */

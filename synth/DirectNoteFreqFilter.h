/*
 * DirectNoteFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef DIRECTNOTEFREQFILTER_H_
#define DIRECTNOTEFREQFILTER_H_

#include "ANoteReceiver.h"
#include "AFreqTransmitter.h"
#include "AFreqFilterChainMember.h"

class DirectNoteFreqFilter : public AFreqTransmitter, public AFreqFilterChainMember {
public:
  DirectNoteFreqFilter();
  void updateFreq();

};

#endif /* DIRECTNOTEFREQFILTER_H_ */

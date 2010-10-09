/*
 * DirectNoteFreqFilter.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef DIRECTNOTEFREQFILTER_H_
#define DIRECTNOTEFREQFILTER_H_

#include "ANoteReceiver.h"
#include "AFreqOffsetTransmitter.h"
#include "AFreqFilterChainMember.h"

class DirectNoteFreqFilter : public AFreqOffsetTransmitter, public AFreqFilterChainMember {
public:
  void updateOffset();
};

#endif /* DIRECTNOTEFREQFILTER_H_ */

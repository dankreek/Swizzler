/*
 * AFreqFilterChainMember.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef AFREQFILTERCHAINMEMBER_H_
#define AFREQFILTERCHAINMEMBER_H_

class FreqFilterChain;

class AFreqFilterChainMember {
public:
  void setParentContainer(FreqFilterChain*);
protected:
  FreqFilterChain *freqChainContainer;
};

inline
void AFreqFilterChainMember::setParentContainer(FreqFilterChain *parent) {
  freqChainContainer = parent;
}

#endif /* AFREQFILTERCHAINMEMBER_H_ */

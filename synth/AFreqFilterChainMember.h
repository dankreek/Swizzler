/** @file AFreqFilterChainMember.h
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#ifndef AFREQFILTERCHAINMEMBER_H_
#define AFREQFILTERCHAINMEMBER_H_

class FreqFilterChain;

/**
 * Abstract class used to provide functionality needed for members of the frequency filter chain.
 */
class AFreqFilterChainMember {
public:
  /**
   * Sets a reference to the filter chain that the inheriting class is a member of
   *
   * @param filterChain	Pointer to the filter chain
   */
  void setParentContainer(FreqFilterChain* filterChain);

protected:

  /// Pointer to the filter chain that this class is a member of
  FreqFilterChain *freqChainContainer;
};

inline void
AFreqFilterChainMember::setParentContainer(FreqFilterChain *parent) {
  freqChainContainer = parent;
}

#endif /* AFREQFILTERCHAINMEMBER_H_ */

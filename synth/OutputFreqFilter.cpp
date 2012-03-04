/** @file OutputFreqFilter.cpp
 *  @date Jan 16, 2011
 */
#include "OutputFreqFilter.h"

OutputFreqFilter::OutputFreqFilter() {
  curOffset = 0;
}

void OutputFreqFilter::recvOffset(int16_t offset) {
  curOffset = offset;
}

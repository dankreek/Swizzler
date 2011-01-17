/*
 * OutputFreqFilter.cpp
 *
 *  Created on: Jan 16, 2011
 *      Author: justin
 */
#include "OutputFreqFilter.h"

OutputFreqFilter::OutputFreqFilter() {
  curOffset = 0;
}

void OutputFreqFilter::recvOffset(int16_t offset) {
  curOffset = offset;
}

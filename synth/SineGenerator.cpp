/** @file SineGenerator.cpp
 *  @date Oct 3, 2010
 */

#include "SineGenerator.h"

SineGenerator::SineGenerator() {
  _incAmount = 0;
  _idxAccum = 0;
}

void SineGenerator::nextTick() {
  _idxAccum += _incAmount;
}

void SineGenerator::setFrequency( uint16_t freq ) {
  _incAmount = ( freq * 0x10000 ) / 1000;
}

int16_t SineGenerator::getCurValue() {
  // Convert _idxAccum (16 bit) to an index between 0-127 (7 bit)
  return _sineTable.getSine( _idxAccum >> 9 );
}

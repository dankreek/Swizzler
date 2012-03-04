/** @file PortamentoFreqFilter.cpp
 *  @date Aug 29, 2010
 */

#include "PortamentoFreqFilter.h"
#include "FreqFilterChain.h"
#include "FreqUtils.h"
#include "Swizzler.h"

PortamentoFreqFilter::PortamentoFreqFilter() {
  reset();
}

void PortamentoFreqFilter::reset() {
  _destPortNote = 0;
  _srcPortNote = 0;
  _curSchlipsOffset = 0;
}

void PortamentoFreqFilter::nextTick() {
  if (_timerCount <= _getEffectivePortTime()) {
    _curSchlipsOffset = _curSchlipsOffset + _offsetIncAmount;
    _timerCount++;
  }
  else {
    _curSchlipsOffset = 0;
  }
}

// TODO - I think this is too highly factored, maybe replace all calls to this with the body of the method
void PortamentoFreqFilter::_sendEffectiveOffset() {
	sendSchlipOffset(_getEffectiveOffset());
}

void PortamentoFreqFilter::_startNewGlide() {
	_timerCount = 0;
	int16_t beginSchlip = ( _srcPortNote - _destPortNote ) * FreqUtils::schlipsDivs;


	_offsetIncAmount = -( beginSchlip << LINEAR_RESOLUTION ) / ((int16_t) _getEffectivePortTime() );
	_curSchlipsOffset = ( beginSchlip << LINEAR_RESOLUTION );
}

bool PortamentoFreqFilter::_isNewNoteStruck() {
	return (( _destPortNote != freqChainContainer->curNoteNum ) ||
			( _srcPortNote  != freqChainContainer->prevNoteNum ));
}

bool PortamentoFreqFilter::_hasPrevNoteBeenStruck() {
	return ( freqChainContainer->prevNoteNum != -1 );
}


void PortamentoFreqFilter::updateOffset() {
	// If no notes have changed, then simply output the current frequency
	if (!_isNewNoteStruck()) {


	}
	// If a note has been played start a new glide
	else {
		// If there was no previous frequency, go directly to the destination frequency
		if (!_hasPrevNoteBeenStruck()) {
			freqChainContainer->prevNoteNum = freqChainContainer->curNoteNum;
			_srcPortNote = freqChainContainer->curNoteNum;
		} else {
			_srcPortNote = freqChainContainer->prevNoteNum;
		}

		_destPortNote = freqChainContainer->curNoteNum;

		_startNewGlide();
	}

	_sendEffectiveOffset();
}

uint16_t PortamentoFreqFilter::_getEffectivePortTime() {
	// TODO - Figure out if this is still accurate. Should probably just measure all time in "ticks" instead of ms
	// Note the +1 is because the timer routine gets called every 2ms (divide by 2)
	return ( Swizzler::portamentoTime >> ( LINEAR_RESOLUTION + 1 ) );
}


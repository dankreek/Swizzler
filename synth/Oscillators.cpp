/** @file Oscillators.cpp
 *  @date Aug 28, 2010
 */

#include "Oscillators.h"
#include "Swizzler.h"
#include "FreqUtils.h"

Oscillators::Oscillators() {
	_curRootNote = 0;
	for (uint8_t i=0; i < VCO_COUNT; i++) {
		_noteOffset[ i ] = 0;
		_lastFreq[ i ] = 0;
	}
}

void Oscillators::noteOn( uint8_t noteNumber, uint8_t velocity ) {
	_curRootNote = noteNumber;
	update();
}

void Oscillators::update() {
	// Update the output frequency for each oscillator
	for ( uint8_t i=0; i < VCO_COUNT; i++ ) { _outputFrequency( i ); }
}

void Oscillators::_outputFrequency( uint8_t voiceNum ) {
	// TODO : Find out why this isn't being done by the Frequency filter chain
	int16_t freqModOffset = Swizzler::freqModEffectChain.getFreqOffset();
	uint16_t outFreq = FreqUtils::modulatedFreq( _curRootNote + _noteOffset[voiceNum], freqModOffset );

	if (outFreq != _lastFreq[voiceNum]) {
		Swizzler::soundChip.setFrequency( voiceNum, outFreq );
		_lastFreq[ voiceNum ] = outFreq;
	}
}

void Oscillators::noteOff( uint8_t noteNumber ) {
  // We really don't need to do any note off stuff here, since the gate stuff's already been done
}

void Oscillators::setNoteOffset( uint8_t oscNum, int8_t offset ) {
	_noteOffset[ oscNum ] = offset;
	_outputFrequency( oscNum );
}


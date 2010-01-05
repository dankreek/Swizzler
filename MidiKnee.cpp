#include "MidiKnee.h"

uint16_t MidiKnee::getValue(uint8_t midiValue) {
	uint16_t out;

	if (midiValue <= kneeX) {
		out = ((uint16_t)kneeY*(uint16_t)midiValue)/kneeX;	
	}
	else {
		out = ((uint16_t)(range-kneeY)*(uint16_t)midiValue)/(127-kneeX); 
	}

	return out;
}

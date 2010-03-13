/*
 * SetParameters.h
 *
 *  Created on: Mar 9, 2010
 *      Author: justin
 */

#ifndef SETPARAMETERS_H_
#define SETPARAMETERS_H_

#include "Swizzler.h"

/**
 * All methods in this class take a 7bit unsigned int as an input which is the
 * size that a MIDI controller provides. This reduces  memory size and makes preset
 * storing and loading much easier.
 *
 * All scaling of controller values to real values are done in these methods
 */
class SetParameters {
public:
	static void setTriLevel(uint8_t);
	static void setSquareLevel(uint8_t);
	static void setSawtoothLevel(uint8_t);
	static void setRandomLevel(uint8_t);
	static void setNoiseLevel(uint8_t);

	static void enablePortamento(uint8_t);
	static void setPortamentoTime(uint8_t);

	static void setPulseWidth(uint8_t);

	static void setAttackTime(uint8_t);
	static void setDecayTime(uint8_t);
	static void setSustainLevel(uint8_t);
	static void setReleaseTime(uint8_t);

	static void enableArpeggio(uint8_t);
	static void setArpeggioTime(uint8_t);
	static void setArpeggioMinNotes(uint8_t);

	static void setBendRange(uint8_t);
};

#endif /* SETPARAMETERS_H_ */

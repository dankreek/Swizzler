/*
 * PresetHandler.cpp
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include "PresetManager.h"
#include "Swizzler.h"

Preset PresetManager::curSettings;


void PresetManager::setInitialSettings() {
}


void PresetManager::applySettings() {
	SetParameters::setAttackTime(curSettings.attackTime);
	SetParameters::setDecayTime(curSettings.decayTime);
	SetParameters::setSustainLevel(curSettings.sustainLevel);
	SetParameters::setReleaseTime(curSettings.releaseTime);

	SetParameters::setTriLevel(curSettings.triLevel);
	SetParameters::setSawtoothLevel(curSettings.sawLevel);
	SetParameters::setSquareLevel(curSettings.sqLevel);
	SetParameters::setRandomLevel(curSettings.randLevel);
	SetParameters::setNoiseLevel(curSettings.noiseLevel);

	SetParameters::setPortamentoTime(curSettings.portamentoTime);
	SetParameters::enablePortamento(curSettings.portamentoTime);

	SetParameters::setArpeggioTime(curSettings.arpeggioTime);
	SetParameters::setArpeggioMinNotes(curSettings.arpeggioMinNotes);
	SetParameters::enableArpeggio(curSettings.arpeggioOn);
}

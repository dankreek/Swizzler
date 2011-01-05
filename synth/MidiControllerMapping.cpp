/*
 * MidiControllerMapping.cpp
 *
 *  Created on: Aug 7, 2010
 *      Author: justin
 *
 * This file needs to be defined for every implementation of the Swizzler platform.
 *
 * This mostly-static class contains a list of instances of itself which contain
 * the mapping from a midi controller number to a function with the signature of
 * "bool func(uint8_t ctrlNum, uint8_t crtlVal)"
 */
#include "MidiControllerMapping.h"
#include "MidiControllerNumbers.h"
#include "SetParameters.h"
#include "PresetManager.h"
#include <stdlib.h>

MidiControllerMapping MidiControllerMapping::controllerList[] = {
    MidiControllerMapping(
        MidiControllerNumbers::modWheel,
        SetParameters::setModWheelLevel),

    // LFO controlls
    MidiControllerMapping(
        MidiControllerNumbers::lfoFreq,
        SetParameters::setLfoFreq),
    MidiControllerMapping(
        MidiControllerNumbers::lfoType,
        SetParameters::setLfoType),

    // Oscillator settings
    MidiControllerMapping(
        MidiControllerNumbers::oscLevel1,
        SetParameters::setOscLevel1),
    MidiControllerMapping(
        MidiControllerNumbers::oscWaveform1,
        SetParameters::setOscWaveform1),

    MidiControllerMapping(
        MidiControllerNumbers::oscLevel2,
        SetParameters::setOscLevel2),
    MidiControllerMapping(
        MidiControllerNumbers::oscWaveform2,
        SetParameters::setOscWaveform2),
    MidiControllerMapping(
        MidiControllerNumbers::oscOffset2,
        SetParameters::setOscOffset2),

    MidiControllerMapping(
        MidiControllerNumbers::oscLevel3,
        SetParameters::setOscLevel3),
    MidiControllerMapping(
        MidiControllerNumbers::oscWaveform3,
        SetParameters::setOscWaveform3),
    MidiControllerMapping(
        MidiControllerNumbers::oscOffset3,
        SetParameters::setOscOffset3),

//    MidiControllerMapping(
//        MidiControllerNumbers::noiseLevel,
//        SetParameters::setNoiseLevel),

    // Set pitch bending range
    MidiControllerMapping(
        MidiControllerNumbers::pitchBendRange,
        SetParameters::setBendRange),

    // Set pulse width
    MidiControllerMapping(
        MidiControllerNumbers::pulseWidth,
        SetParameters::setPulseWidth),

    // Portamento Controlls
    MidiControllerMapping(
        MidiControllerNumbers::portamentoOnOff,
        SetParameters::enablePortamento),
    MidiControllerMapping(
        MidiControllerNumbers::portamentoTime,
        SetParameters::setPortamentoTime),

    // Envelope timing and level
    MidiControllerMapping(
        MidiControllerNumbers::attackTime,
        SetParameters::setAttackTime),
    MidiControllerMapping(
        MidiControllerNumbers::decayTime,
        SetParameters::setDecayTime),
    MidiControllerMapping(
        MidiControllerNumbers::sustainLevel,
        SetParameters::setSustainLevel),
    MidiControllerMapping(
        MidiControllerNumbers::releaseTime,
        SetParameters::setReleaseTime),

    // Arpeggiator settings
    MidiControllerMapping(
        MidiControllerNumbers::arpOnOff,
        SetParameters::enableArpeggio),
    MidiControllerMapping(
        MidiControllerNumbers::arpMinNotes,
        SetParameters::setArpeggioMinNotes),
    MidiControllerMapping(
        MidiControllerNumbers::arpTime,
        SetParameters::setArpeggioTime),
    MidiControllerMapping(
        MidiControllerNumbers::arpDirection,
        SetParameters::setArpeggioDirection),

    // Store and load presets
    MidiControllerMapping(
        MidiControllerNumbers::storePreset,
        PresetManager::storePreset),

    // Signifies the end of the list
    MidiControllerMapping(endOfMappingList, NULL)
};

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
 *
 * Because this list is created at compile time the length of the mapping array
 * must be recorded here by hand.
 */
#include "MidiControllerMapping.h"
#include "MidiControllerNumbers.h"
#include "SetParameters.h"
#include "PresetManager.h"
#include <stdlib.h>

//uint8_t MidiControllerMapping::listLength = 0;

MidiControllerMapping MidiControllerMapping::controllerList[] = {
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
        SetParameters::setAttackTime),

    // Store and load presets
    MidiControllerMapping(
        MidiControllerNumbers::storePreset,
        PresetManager::storePreset),

    // Signifies the end of the list
    MidiControllerMapping(endOfMappingList, NULL)
};

/** @file MidiControllerMapping.cpp
 *  @date Aug 7, 2010
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
        MidiControllerNumbers::MODULATION_WHEEL,
        SetParameters::setModWheelLevel),

    // LFO controlls
    MidiControllerMapping(
        MidiControllerNumbers::LFO_FREQUENCY,
        SetParameters::setLfoFreq),
    MidiControllerMapping(
        MidiControllerNumbers::LFO_TYPE,
        SetParameters::setLfoModulationParameter),

    // Oscillator settings
    MidiControllerMapping(
        MidiControllerNumbers::VCO1_LEVEL,
        SetParameters::setOscLevel1),
    MidiControllerMapping(
        MidiControllerNumbers::VCO1_WAVEFORM,
        SetParameters::setOscWaveform1),

    MidiControllerMapping(
        MidiControllerNumbers::VCO2_LEVEL,
        SetParameters::setOscLevel2),
    MidiControllerMapping(
        MidiControllerNumbers::VCO2_WAVEFORM,
        SetParameters::setOscWaveform2),
    MidiControllerMapping(
        MidiControllerNumbers::VCO2_NOTE_OFFSET,
        SetParameters::setOscOffset2),

    MidiControllerMapping(
        MidiControllerNumbers::VCO3_LEVEL,
        SetParameters::setOscLevel3),
    MidiControllerMapping(
        MidiControllerNumbers::VCO3_WAVEFORM,
        SetParameters::setOscWaveform3),
    MidiControllerMapping(
        MidiControllerNumbers::VCO3_NOTE_OFFSET,
        SetParameters::setOscOffset3),

//    MidiControllerMapping(
//        MidiControllerNumbers::noiseLevel,
//        SetParameters::setNoiseLevel),

    // Set pitch bending range
    MidiControllerMapping(
        MidiControllerNumbers::PITCHBEND_RANGE,
        SetParameters::setBendRange),

    // Set pulse width
    MidiControllerMapping(
        MidiControllerNumbers::PULSE_WIDTH,
        SetParameters::setPulseWidth),

    // Portamento Controlls
    MidiControllerMapping(
        MidiControllerNumbers::ENABLE_PORTAMENTO,
        SetParameters::enablePortamento),
    MidiControllerMapping(
        MidiControllerNumbers::PORTAMENTO_TIME,
        SetParameters::setPortamentoTime),

    // Envelope timing and level
    MidiControllerMapping(
        MidiControllerNumbers::ATTACK_TIME,
        SetParameters::setAttackTime),
    MidiControllerMapping(
        MidiControllerNumbers::DECAY_TIME,
        SetParameters::setDecayTime),
    MidiControllerMapping(
        MidiControllerNumbers::SUSTAIN_LEVEL,
        SetParameters::setSustainLevel),
    MidiControllerMapping(
        MidiControllerNumbers::RELEASE_TIME,
        SetParameters::setReleaseTime),

    // Arpeggiator settings
    MidiControllerMapping(
        MidiControllerNumbers::ENABLE_ARPEGGIATOR,
        SetParameters::enableArpeggio),
    MidiControllerMapping(
        MidiControllerNumbers::MINIMUM_ARPEGGIO_NOTES,
        SetParameters::setArpeggioMinNotes),
    MidiControllerMapping(
        MidiControllerNumbers::ARPEGGIO_TIME,
        SetParameters::setArpeggioTime),
    MidiControllerMapping(
        MidiControllerNumbers::ARPEGGIO_DIRECTION,
        SetParameters::setArpeggioDirection),

    // Store and load presets
    // TODO - Probably should take these out of MIDI and only use surface controlls. 
    MidiControllerMapping(
        MidiControllerNumbers::SAVE_PRESET,
        PresetManager::storePreset),

    // Signifies the end of the list
    MidiControllerMapping(endOfMappingList, NULL)
};

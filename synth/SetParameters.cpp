/*
 * SetParameters.cpp
 *
 *  Created on: Mar 9, 2010
 *      Author: justin
 */

#include <inttypes.h>
#include "DisplayOutput.h"
#include "SetParameters.h"
#include "KnobKnee.h"
#include "PresetManager.h"
#include "Swizzler.h"

// Knees to define how midi controls work, and the range for the control
KnobKnee portTimeKnee = KnobKnee(71, 20, 110, 250, 2000);
KnobKnee attackTimeKnee = KnobKnee(71, 100, 103, 1000, 8000);
KnobKnee decRelTimeKnee = KnobKnee(71, 300, 103, 3000, 24000);	// Decay/release time knee
KnobKnee arpTimeKnee = KnobKnee(71, 25, 103, 250, 1000);		// Arpeggio time (ms per note)

uint8_t EEMEM portamentoStr[] = {"Portamento"};
uint8_t EEMEM ArpeggioStr[] = {"Arpeggiator"};

void SetParameters::enablePortamento(uint8_t p) {
  Swizzler::oscillators.setPortamento((p >= 64) ? true : false);
  PresetManager::curSettings.portamentoOn = p;

  DisplayOutput::clearDisplay();
  DisplayOutput::printEepromString(portamentoStr);
}

void SetParameters::setLfoFreq(uint8_t p) {
  // Note that the actual frequency is p/4. This yields a range of between 0 and 31hz
  Swizzler::lfoController.sinGenerator.setFrequency(p);
  PresetManager::curSettings.lfoFreq = p;
}

void SetParameters::setLfoType(uint8_t p) {
  Swizzler::lfoController.setLfoMode((LfoController::LfoMode)p);
  PresetManager::curSettings.lfoType = p;
}

void SetParameters::setPortamentoTime(uint8_t p) {
  Swizzler::portamentoTime = portTimeKnee.getValue(p);
  PresetManager::curSettings.portamentoTime = p;
}

void SetParameters::setPulseWidth(uint8_t p) {
  Swizzler::soundChip.setGlobalPulseWidth(p << 1);
  PresetManager::curSettings.pulseWidth = p;
}

void SetParameters::setAttackTime(uint8_t p) {
  Swizzler::soundChip.setAttackTime(attackTimeKnee.getValue(p));
  PresetManager::curSettings.attackTime = p;
}

void SetParameters::setDecayTime(uint8_t p) {
  Swizzler::soundChip.setDecayTime(decRelTimeKnee.getValue(p));
  PresetManager::curSettings.decayTime = p;
}

void SetParameters::setSustainLevel(uint8_t p) {
  Swizzler::soundChip.setSustainLevel(p<<1);
  PresetManager::curSettings.sustainLevel = p;
}

void SetParameters::setReleaseTime(uint8_t p) {
  Swizzler::soundChip.setReleaseTime(decRelTimeKnee.getValue(p));
  PresetManager::curSettings.releaseTime = p;
}

void SetParameters::enableArpeggio(uint8_t p) {
  Swizzler::enableArpeggio((p >= 64) ? true : false);
  PresetManager::curSettings.arpeggioOn = p;
}

void SetParameters::setArpeggioTime(uint8_t p) {
  // Tweaked to make 10 the minimum value.
  // XXX: Is this the best way to go about it?
  //NoteManager::arpManager.arpTime = arpTimeKnee.getValue(p)+10;
  Swizzler::arp.setArpTime(arpTimeKnee.getValue(p)+10);
  PresetManager::curSettings.arpeggioTime = p;
}

void SetParameters::setArpeggioMinNotes(uint8_t p) {
  // Ranges from 1-16
  //NoteManager::arpManager.minNotes = (p >> 3)+1;
  Swizzler::arp.setMinNotes((p >> 3)+1);
  PresetManager::curSettings.arpeggioMinNotes = p;
}

void SetParameters::setBendRange(uint8_t p) {
  // Bend range (in +/- half-steps) ranges from 0-15
  //OscillatorMux::bendRange = (p >> 3);
  PresetManager::curSettings.bendRange = p;
}

void SetParameters::setWaveform(uint8_t voiceNum, uint8_t wf) {
  SoundDriver::WaveformType waveForm;

  switch (wf) {
  case 0:
    waveForm = SoundDriver::triangleWave;
    break;
  case 1:
    waveForm = SoundDriver::sawtoothWave;
    break;
  case 2:
    waveForm = SoundDriver::reverseSawtoothWave;
    break;
  case 3:
    waveForm = SoundDriver::squareWave;
    break;
  default:
    waveForm = SoundDriver::noiseWave;
  }

  Swizzler::soundChip.setWaveform(voiceNum,waveForm);
}

// @offset is the raw midi controller value (0-127)
void SetParameters::setVoiceOffset(uint8_t voiceNum, uint8_t offset) {
  int8_t relOfs = (int8_t)(offset >> 2)-16;
  Swizzler::oscillators.setNoteOffset(voiceNum, relOfs);
}

void SetParameters::setVoiceLevel(uint8_t voiceNum, uint8_t level) {
  Swizzler::soundChip.setVoiceLevel(voiceNum, level<<1);
}

void SetParameters::setOscLevel1(uint8_t p) {
  setVoiceLevel(0, p);
  PresetManager::curSettings.voiceLevel1 = p;
}

void SetParameters::setOscLevel2(uint8_t p) {
  setVoiceLevel(1, p);
  PresetManager::curSettings.voiceLevel2 = p;
}

void SetParameters::setOscLevel3(uint8_t p) {
  setVoiceLevel(2, p);
  PresetManager::curSettings.voiceLevel3 = p;
}

void SetParameters::setOscWaveform1(uint8_t p) {
  setWaveform(0, p);
  PresetManager::curSettings.waveform1 = p;
}

void SetParameters::setOscWaveform2(uint8_t p) {
  setWaveform(1, p);
  PresetManager::curSettings.waveform2 = p;
}

void SetParameters::setOscWaveform3(uint8_t p) {
  setWaveform(2, p);
  PresetManager::curSettings.waveform3 = p;
}

void SetParameters::setOscOffset2(uint8_t p) {
  setVoiceOffset(1, p);
  PresetManager::curSettings.freqOffset2 = p;
}

void SetParameters::setOscOffset3(uint8_t p) {
  setVoiceOffset(2, p);
  PresetManager::curSettings.freqOffset3 = p;
}

void SetParameters::setArpeggioDirection(uint8_t p) {
  Swizzler::arp.setArpDirection(ArpeggiatorNoteFilter::ArpeggioDirection(p));
  PresetManager::curSettings.arpeggioDirection = p;
}

void SetParameters::setModWheelLevel(uint8_t p) {
  Swizzler::modWheelLevel = p;
}

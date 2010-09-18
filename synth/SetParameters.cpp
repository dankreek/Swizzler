/*
 * SetParameters.cpp
 *
 *  Created on: Mar 9, 2010
 *      Author: justin
 */

#include "SetParameters.h"
#include "KnobKnee.h"
#include "PresetManager.h"
#include "Swizzler.h"

// Knees to define how midi controls work, and the range for the control
KnobKnee portTimeKnee = KnobKnee(2000, 95, 500);
KnobKnee attackTimeKnee = KnobKnee(8000, 95, 1000);
KnobKnee decRelTimeKnee = KnobKnee(24000, 95, 2400);	// Decay/release time knee
KnobKnee arpTimeKnee = KnobKnee(1000, 95, 250);			// Arpeggio time (ms per note)

void SetParameters::enablePortamento(uint8_t p) {
  Swizzler::oscillators.setPortamento((p > 0) ? true : false);
  PresetManager::curSettings.portamentoOn = p;
}

void SetParameters::setPortamentoTime(uint8_t p) {
  //for (uint8_t i; i < Swizzler::numOscillators; i++)
  //  FrequencyManager::managers[i].portMan.time = portTimeKnee.getValue(p);
  //OscillatorMux::setPortamentoTime(portTimeKnee.getValue(p));

  Swizzler::portamentoTime = portTimeKnee.getValue(p);
  PresetManager::curSettings.portamentoTime = p;
}

void SetParameters::setPulseWidth(uint8_t p) {
  //Pulse width is a 4 bit value because the wavetables are 4bits long
//	Wavetable::pulseWidth = (p >> 3);
//	Wavetable::genSquare();
  for (int i=0; i < 4; i++) Swizzler::soundChip.setPuleseWidth(i, (uint16_t)p<<9);
  PresetManager::curSettings.pulseWidth = p;
}

void SetParameters::setAttackTime(uint8_t p) {
  for (int i=0; i < 4; i++) Swizzler::soundChip.setAttackTime(i, attackTimeKnee.getValue(p));
  PresetManager::curSettings.attackTime = p;
}

void SetParameters::setDecayTime(uint8_t p) {
  for (int i=0; i < 4; i++) Swizzler::soundChip.setDecayTime(i, decRelTimeKnee.getValue(p));
  PresetManager::curSettings.decayTime = p;
}

void SetParameters::setSustainLevel(uint8_t p) {
  for (int i=0; i < 4; i++) Swizzler::soundChip.setSustainLevel(i, p<<1);
  PresetManager::curSettings.sustainLevel = p;
}

void SetParameters::setReleaseTime(uint8_t p) {
  for (int i=0; i < 4; i++) Swizzler::soundChip.setReleaseTime(i, decRelTimeKnee.getValue(p));
  PresetManager::curSettings.releaseTime = p;
}

void SetParameters::enableArpeggio(uint8_t p) {
  //NoteManager::enableArpeggio((p > 0) ? true : false);
  PresetManager::curSettings.arpeggioOn = p;
}

void SetParameters::setArpeggioTime(uint8_t p) {
  // Tweaked to make 10 the minimum value.
  // XXX: Is this the best way to go about it?
  //NoteManager::arpManager.arpTime = arpTimeKnee.getValue(p)+10;
  PresetManager::curSettings.arpeggioTime = p;
}

void SetParameters::setArpeggioMinNotes(uint8_t p) {
  // Ranges from 1-16
  //NoteManager::arpManager.minNotes = (p >> 3)+1;
  PresetManager::curSettings.arpeggioMinNotes = p;
}

void SetParameters::setBendRange(uint8_t p) {
  // Bend range (in +/- half-steps) ranges from 0-15
  //OscillatorMux::bendRange = (p >> 3);
  PresetManager::curSettings.bendRange = p;
}

void SetParameters::setWaveform(uint8_t voiceNum, uint8_t wf) {
  SoundDriver::WaveformType waveForm;
  if (wf < 32)
    waveForm = SoundDriver::triangleWave;
  else if (wf < 64)
    waveForm = SoundDriver::sawtoothWave;
  else if (wf < 96)
    waveForm = SoundDriver::reverseSawtoothWave;
  else
    waveForm = SoundDriver::squareWave;

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

void SetParameters::setNoiseLevel(uint8_t p) {
  setVoiceLevel(3, p);
  PresetManager::curSettings.noiseLevel = p;
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

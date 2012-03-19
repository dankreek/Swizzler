/** @ file SetParameters.cpp
 *  @date Mar 9, 2010
 */

#include <inttypes.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "SetParameters.h"
#include "SurfaceControlManager.h"
#include "KnobKnee.h"
#include "PresetManager.h"
#include "Swizzler.h"
#include "ArpeggiatorNoteFilter.h"

// Curves to define how MIDI controls work, and the range for the control
// TODO - Make these private members of the class
KnobKnee portTimeKnee   = KnobKnee(71, 150, 103, 500, 2000);
KnobKnee attackTimeKnee = KnobKnee(71, 100, 103, 500, 4000);
KnobKnee decRelTimeKnee = KnobKnee(71, 300, 103, 3000, 24000);
KnobKnee arpTimeKnee    = KnobKnee(71, 25, 103, 250, 1000);		// Arpeggio time (ms per note)

uint8_t EEMEM portamentoStr[]   = "Portamento";
uint8_t EEMEM portTimeStr[]     = "Portamento Time";
uint8_t EEMEM ArpeggioStr[]     = "Arpeggiator";
uint8_t EEMEM arpTimeStr[]      = "Arp. Time";
uint8_t EEMEM arpMinNotesStr[]  = "Arp. Notes";
uint8_t EEMEM arpDirectionStr[] = "Arp. Direction";
uint8_t EEMEM setLfoFreqStr[]   = "LFO Freq.";
uint8_t EEMEM setLfoTypeStr[]   = "LFO Type";
uint8_t EEMEM pulseWidthStr[]   = "Pulsewidth";
uint8_t EEMEM attackTimeStr[]   = "Attack";
uint8_t EEMEM decayTimeStr[]    = "Decay";
uint8_t EEMEM sustainLevelStr[] = "Sustain";
uint8_t EEMEM releaseTimeStr[]  = "Release";
uint8_t EEMEM setWaveformStr[]  = "Waveform VCO";
uint8_t EEMEM setOscOffset[]    = "Offset VCO";
uint8_t EEMEM setOscLevel[]     = "Level VCO";
uint8_t EEMEM bendRangeStr[]    = "Bend Range";

char onStr[]  = "On";
char offStr[] = "Off";

void SetParameters::enablePortamento(uint8_t p) {
  bool onOff = (p >= 64) ? true : false;
  Swizzler::freqModEffectChain.setPortamento(onOff);
  PresetManager::curSettings.portamentoOn = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(portamentoStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%10s (%3d)", _onOffStr(onOff), p);
}

void SetParameters::setLfoFreq(uint8_t p) {

	// Note that the actual frequency is p/4. This yields a range of between 0 and 31hz
	Swizzler::lfoController.sinGenerator.setFrequency(p);
	PresetManager::curSettings.lfoFreq = p;

	SurfaceControlManager::displayOut.clear();
	SurfaceControlManager::displayOut.writeEepromString(setLfoFreqStr, 0, 0);
	SurfaceControlManager::displayOut.printf(1, (char*)"%8dhz (%3d)", p>>2, p);
}

void SetParameters::setLfoModulationParameter(uint8_t p) {
  LfoController::LfoMode mode = (LfoController::LfoMode)p;
  Swizzler::lfoController.setLfoMode(mode);
  PresetManager::curSettings.lfoType = p;

  const char *modeStr;
  switch (mode) {
  case  LfoController::frequencyModulation:
    modeStr = "Frequency Mod.";
    break;
  case LfoController::pulsewidthModulation:
    modeStr = "Pulse Width Mod.";
    break;
  }

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(setLfoTypeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%16s", modeStr);
}

void SetParameters::setPortamentoTime(uint8_t p) {
  Swizzler::portamentoTime = portTimeKnee.getValue(p);
  PresetManager::curSettings.portamentoTime = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(portTimeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%8dms (%3d)", Swizzler::portamentoTime, p);
}

void SetParameters::setPulseWidth(uint8_t p) {
  uint8_t pulseWidth = (p << 1);
  Swizzler::soundChip.setGlobalPulseWidth(pulseWidth);
  PresetManager::curSettings.pulseWidth = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(pulseWidthStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%6d/254 (%3d)", pulseWidth, p);
}

void SetParameters::setAttackTime(uint8_t p) {
  uint16_t attackTime = attackTimeKnee.getValue(p);
  Swizzler::soundChip.setAttackTime(attackTime);
  PresetManager::curSettings.attackTime = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(attackTimeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%8dms (%3d)", attackTime, p);
}

void SetParameters::setDecayTime(uint8_t p) {
  uint16_t decayTime = decRelTimeKnee.getValue(p);
  Swizzler::soundChip.setDecayTime(decayTime);
  PresetManager::curSettings.decayTime = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(decayTimeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%8dms (%3d)", decayTime, p);
}

void SetParameters::setSustainLevel(uint8_t p) {
  uint8_t sustain = (p << 1);
  Swizzler::soundChip.setSustainLevel(sustain);
  PresetManager::curSettings.sustainLevel = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(sustainLevelStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%6d/254 (%3d)", sustain, p);
}

void SetParameters::setReleaseTime(uint8_t p) {
  uint16_t releaseTime = decRelTimeKnee.getValue(p);
  Swizzler::soundChip.setReleaseTime(releaseTime);
  PresetManager::curSettings.releaseTime = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(releaseTimeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%8dms (%3d)", releaseTime, p);
}

void SetParameters::enableArpeggio(uint8_t p) {
  bool onOff = (p >= 64) ? true : false;
  Swizzler::enableArpeggio(onOff);
  PresetManager::curSettings.arpeggioOn = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(ArpeggioStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%10s (%3d)", _onOffStr(onOff), p);
}

void SetParameters::setArpeggioTime(uint8_t p) {
  // Tweaked to make 10 the minimum value.
  // TODO Figure out if this is the best way to go about it
  uint16_t arpTime = arpTimeKnee.getValue(p) + 10;
  Swizzler::arp.setArpTime(arpTime);
  PresetManager::curSettings.arpeggioTime = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(arpTimeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%8dms (%3d)", arpTime, p);
}

void SetParameters::setArpeggioMinNotes(uint8_t p) {
  // Ranges from 1-8
  uint8_t minNotes = (p >> 4) + 1;
  Swizzler::arp.setMinNotes(minNotes);
  PresetManager::curSettings.arpeggioMinNotes = p;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(arpMinNotesStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%4d notes (%3d)", minNotes, p);
}

void SetParameters::setBendRange(uint8_t p) {
  // Bend range (in +/- schlips). There's 32 schlips in every half step
  uint8_t bendRange = p >> 3;
  PresetManager::curSettings.bendRange = p;
  Swizzler::bendRange = bendRange * 32;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(bendRangeStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%5d semi-tones", bendRange);
}

void SetParameters::_setWaveform(uint8_t voiceNum, uint8_t wf) {
  SoundDriver::WaveformType waveForm;

  const char* waveName;
  switch (wf) {
  case 0:
    waveForm = SoundDriver::triangleWave;
    waveName = "Triangle";
    break;
  case 1:
    waveForm = SoundDriver::sawtoothWave;
    waveName = "Sawtooth";
    break;
  case 2:
    waveForm = SoundDriver::reverseSawtoothWave;
    waveName = "Rev. Sawtooth";
    break;
  case 3:
    waveForm = SoundDriver::squareWave;
    waveName = "Square";
    break;
    // TODO - The default should be a no-op, it is documented this way
  default:
    waveForm = SoundDriver::noiseWave;
    waveName = "Noise";
  }

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.printf(0, (char*)"%14d", voiceNum+1);
  SurfaceControlManager::displayOut.writeEepromString(setWaveformStr, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%16s", waveName);

  Swizzler::soundChip.setWaveform(voiceNum,waveForm);
}

// @offset is the raw midi controller value (0-127)
void SetParameters::_setVoiceOffset(uint8_t voiceNum, uint8_t offset) {
  int8_t relOfs = (int8_t)(offset >> 2)-16;
  Swizzler::oscillators.setNoteOffset(voiceNum, relOfs);

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.printf(0, (char*)"%12d", voiceNum+1);
  SurfaceControlManager::displayOut.writeEepromString(setOscOffset, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%5d semi-tones", relOfs);
}

void SetParameters::_setVoiceLevel(uint8_t voiceNum, uint8_t level) {
  uint8_t outLevel = level << 1;
  Swizzler::soundChip.setVoiceLevel(voiceNum, outLevel);

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.printf(0, (char*)"%11d", voiceNum+1);
  SurfaceControlManager::displayOut.writeEepromString(setOscLevel, 0, 0);
  SurfaceControlManager::displayOut.printf(1, (char*)"%12d/254", outLevel);
}

void SetParameters::setOscLevel1(uint8_t p) {
  _setVoiceLevel(0, p);
  PresetManager::curSettings.voiceLevel1 = p;
}

void SetParameters::setOscLevel2(uint8_t p) {
  _setVoiceLevel(1, p);
  PresetManager::curSettings.voiceLevel2 = p;
}

void SetParameters::setOscLevel3(uint8_t p) {
  _setVoiceLevel(2, p);
  PresetManager::curSettings.voiceLevel3 = p;
}

void SetParameters::setOscWaveform1(uint8_t p) {
  _setWaveform(0, p);
  PresetManager::curSettings.waveform1 = p;
}

void SetParameters::setOscWaveform2(uint8_t p) {
  _setWaveform(1, p);
  PresetManager::curSettings.waveform2 = p;
}

void SetParameters::setOscWaveform3(uint8_t p) {
  _setWaveform(2, p);
  PresetManager::curSettings.waveform3 = p;
}

void SetParameters::setOscOffset2(uint8_t p) {
  _setVoiceOffset(1, p);
  PresetManager::curSettings.freqOffset2 = p;
}

void SetParameters::setOscOffset3(uint8_t p) {
  _setVoiceOffset(2, p);
  PresetManager::curSettings.freqOffset3 = p;
}

void SetParameters::setArpeggioDirection( uint8_t p ) {
	Swizzler::arp.setArpDirection( ArpeggiatorNoteFilter::ArpeggioDirection( p ) );
	PresetManager::curSettings.arpeggioDirection = p;

	// TODO Define some default behavior
	const char *dirStr;
	switch ( ArpeggiatorNoteFilter::ArpeggioDirection( p ) ) {
		case ArpeggiatorNoteFilter::up:
			dirStr = "Up";
			break;
		case ArpeggiatorNoteFilter::down:
			dirStr = "Down";
			break;
		case ArpeggiatorNoteFilter::random:
			dirStr = "Random";
			break;
	}

	SurfaceControlManager::displayOut.clear();
	SurfaceControlManager::displayOut.writeEepromString( arpDirectionStr, 0, 0 );
	SurfaceControlManager::displayOut.printf( 1, (char*)"%10s (%3d)", dirStr, p );
}

void SetParameters::setModWheelLevel(uint8_t p) {
  Swizzler::modWheelLevel = p;
}

char* SetParameters::_onOffStr(bool isOn) {
  if (isOn) {
    return onStr;
  } else {
    return offStr;
  }
}

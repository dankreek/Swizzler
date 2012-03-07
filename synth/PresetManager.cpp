/*
 * PresetHandler.cpp
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include "PresetManager.h"
#include "Swizzler.h"
#include <avr/eeprom.h>
#include "Wire.h"
#include "ExternalEeprom.h"

uint8_t EEMEM factoryDefaultsStr[] = "Factory Defaults";
uint8_t EEMEM restoredStr[]        = "Restored";
uint8_t EEMEM savePresetStr[]      = "Save Preset #";
uint8_t EEMEM loadPresetStr[]      = "Preset #";

ExternalEeprom PresetManager::presetEeprom = ExternalEeprom(eepromAddress);
SwizzlerPatch PresetManager::curSettings;
uint8_t	PresetManager::curPreset;

// This is used to read in a preset from EEPROM before its settings are applied
SwizzlerPatch readStorage;

void PresetManager::setFactoryDefaults() {
  SurfaceControlManager::displayOut.isOutputOn = false;

  for (curPreset=0; curPreset < 128; curPreset++) {
    setDefaultPreset();
    storePreset(0);
  }

  loadPreset(0);
  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.writeEepromString(factoryDefaultsStr, 0, 0);
  SurfaceControlManager::displayOut.writeEepromString(restoredStr, 1, 4);
  SurfaceControlManager::displayOut.isOutputOn = true;
}

void PresetManager::setDefaultPreset() {
  readStorage.lfoFreq = 64;
  readStorage.lfoType = LfoController::frequencyModulation;

  readStorage.attackTime = 0;
  readStorage.decayTime = 0;
  readStorage.sustainLevel = 127;
  readStorage.releaseTime = 0;

  readStorage.waveform1 = SoundDriver::triangleWave;
  readStorage.voiceLevel1 = 127;

  readStorage.waveform2 = SoundDriver::triangleWave;
  readStorage.voiceLevel2 = 0;
  readStorage.freqOffset2 = 64;

  readStorage.waveform3 = SoundDriver::triangleWave;
  readStorage.voiceLevel3 = 0;
  readStorage.freqOffset3 = 64;

  readStorage.pulseWidth = 64;

  readStorage.portamentoTime = 32;
  readStorage.portamentoOn = false;

  readStorage.arpeggioTime = 64;
  readStorage.arpeggioMinNotes = 0;
  readStorage.arpeggioOn = false;
  readStorage.arpeggioDirection = ArpeggiatorNoteFilter::up;

  readStorage.bendRange = 16;

  applyPreset(&readStorage);
}


void PresetManager::storePreset(uint8_t shim) {
  const uint8_t* p = (const uint8_t*)(const void*)&curSettings;
  uint16_t presetOfs = curPreset * sizeof(SwizzlerPatch);

  // Store preset to external EEPROM
  presetEeprom.writeBlock(
    curPreset * ExternalEeprom::PAGE_SIZE,
    (uint8_t*)(void*)&curSettings,
    sizeof(SwizzlerPatch));

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.printf(0, (char*)"%16d", curPreset);
  SurfaceControlManager::displayOut.writeEepromString(savePresetStr, 0, 0);
}

void PresetManager::loadPreset(uint8_t patchNum) {
  if (patchNum > 127) return;
  uint8_t* p = (uint8_t*)&readStorage;

  uint16_t presetOfs = patchNum * sizeof(SwizzlerPatch);

  // Read block from external EEPROM
  presetEeprom.readBlock(
    patchNum*ExternalEeprom::PAGE_SIZE,
    p,
    sizeof(SwizzlerPatch));

  applyPreset((SwizzlerPatch*)p);

  curPreset = patchNum;

  SurfaceControlManager::displayOut.clear();
  SurfaceControlManager::displayOut.printf(0, (char*)"        %d", patchNum);
  SurfaceControlManager::displayOut.writeEepromString(loadPresetStr, 0, 0);
}

void PresetManager::applyPreset(SwizzlerPatch *presetPtr) {
  SetParameters::setLfoFreq(presetPtr->lfoFreq);
  SetParameters::setLfoType(presetPtr->lfoType);

  SetParameters::setAttackTime(presetPtr->attackTime);
  SetParameters::setDecayTime(presetPtr->decayTime);
  SetParameters::setSustainLevel(presetPtr->sustainLevel);
  SetParameters::setReleaseTime(presetPtr->releaseTime);

  SetParameters::setOscWaveform1(presetPtr->waveform1);
  SetParameters::setOscLevel1(presetPtr->voiceLevel1);

  SetParameters::setOscWaveform2(presetPtr->waveform2);
  SetParameters::setOscLevel2(presetPtr->voiceLevel2);
  SetParameters::setOscOffset2(presetPtr->freqOffset2);

  SetParameters::setOscWaveform3(presetPtr->waveform3);
  SetParameters::setOscLevel3(presetPtr->voiceLevel3);
  SetParameters::setOscOffset3(presetPtr->freqOffset3);

  SetParameters::setPulseWidth(presetPtr->pulseWidth);

  SetParameters::setPortamentoTime(presetPtr->portamentoTime);
  SetParameters::enablePortamento(presetPtr->portamentoOn);

  SetParameters::setArpeggioTime(presetPtr->arpeggioTime);
  SetParameters::setArpeggioMinNotes(presetPtr->arpeggioMinNotes);
  SetParameters::setArpeggioDirection(presetPtr->arpeggioDirection);
  SetParameters::enableArpeggio(presetPtr->arpeggioOn);

  SetParameters::setBendRange(presetPtr->bendRange);
}

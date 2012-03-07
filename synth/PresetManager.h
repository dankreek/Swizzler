/*
 * PresetHandler.h
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include <inttypes.h>
#include "SwizzlerPatch.h"
#include "ExternalEeprom.h"

#ifndef PRESETHANDLER_H_
#define PRESETHANDLER_H_

class PresetManager {
public:
  // The current controller values that the synth is using
  static SwizzlerPatch curSettings;

  // The current preset number that's loaded
  static uint8_t curPreset;

  // Load and set a preset by its number (0-127)
  static void loadPreset(uint8_t);

  // Save the current settings in curSettings to the currently selected preset
  // (the parameter's a dummy parameter so that the function can be hooked into a MidiControllerMapping
  static void storePreset(uint8_t);

  // If this is the first boot of the Swizzler, set the default settings
  static void setFactoryDefaults();

  // Save the current settings into EEPROM for restore on next bootup
  static void savePoweronSettings();

  // Load the saved power-on settings
  static void loadPoweronSettings();

  // Replace the current patch with a default (but don't save it to EEPROM)
  static void setDefaultPreset();
private:
  // Apply each parameter in the passed-in preset
  static void applyPreset(SwizzlerPatch*);

  static ExternalEeprom presetEeprom;
  static const uint8_t eepromAddress = 0x50;
};

#endif /* PRESETHANDLER_H_ */

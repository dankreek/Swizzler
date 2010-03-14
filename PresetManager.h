/*
 * PresetHandler.h
 *
 *  Created on: Mar 13, 2010
 *      Author: justin
 */

#include <inttypes.h>
#include "Preset.h"

#ifndef PRESETHANDLER_H_
#define PRESETHANDLER_H_

class PresetManager {
	public:
	// The current controller values that the synth is using
	static Preset curSettings;

	static uint16_t presetTimer;

	// Load and set a preset by its number (0-127)
	static void loadPreset(uint8_t);

	// Save the current settings in curSettings to a preset number (0-127)
	static void storePreset(uint8_t);

	// If this is the first boot of the swizzler, set the default settings
	static void setInitialSettings();

	// Save the current seetings into EEPROM for restore on next bootup
	static void savePoweronSettings();

	// Load the saved power-on settings
	static void loadPoweronSettings();
};

#endif /* PRESETHANDLER_H_ */

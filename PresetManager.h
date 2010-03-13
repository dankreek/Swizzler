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

	// Load a preset by its number (0-127) and store in curSettings
	static void loadPreset(uint8_t);

	// Save the current settings in curSettings to a preset number (0-127)
	static void storePreset(uint8_t);

	// Apply all curSettings to the synthesizer
	static void applySettings();

	// If this is the first boot of the swizzler, set the default settings
	static void setInitialSettings();
};

#endif /* PRESETHANDLER_H_ */

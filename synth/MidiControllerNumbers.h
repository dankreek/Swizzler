/** @file MidiControllerNumbers.h
 *  @date Aug 10, 2010
 */
#ifndef MIDICONTROLLERNUMBERS_H_
#define MIDICONTROLLERNUMBERS_H_

#include <inttypes.h>

/**
 * This class is a container for all the mappings of Swizzler Effect to MIDI controller numbers.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class MidiControllerNumbers {
public:
	/// Modulation level
	static const uint8_t MODULATION_WHEEL = 1;

	/// Set LFO frequency
	static const uint8_t LFO_FREQUENCY = 85;

	/// Set LFO type (Frequency modulation or Pulse width Modulation)
	static const uint8_t LFO_TYPE      = 86;

	/// Enable/disable portamento
	static const uint8_t ENABLE_PORTAMENTO = 65;
	/// Portamento glide time
	static const uint8_t PORTAMENTO_TIME   = 5;

	/// Oscillator 1 level
	static const uint8_t VCO1_LEVEL    = 20;
	/// Set oscillator 1 waveform
	static const uint8_t VCO1_WAVEFORM = 21;

	/// Oscillator 2 level
	static const uint8_t VCO2_LEVEL       = 22;
	/// Set oscillator 2 waveform
	static const uint8_t VCO2_WAVEFORM    = 23;
	/// Set oscillator 2 note offset
	static const uint8_t VCO2_NOTE_OFFSET = 24;

	/// Oscillator 3 level
	static const uint8_t VCO3_LEVEL       = 25;
	/// Set oscillator 3 waveform
	static const uint8_t VCO3_WAVEFORM    = 26;
	/// Set oscillator 3 note offset
	static const uint8_t VCO3_NOTE_OFFSET = 27;

//  static const uint8_t noiseLevel = 28;

	/// Pitchbend range
	static const uint8_t PITCHBEND_RANGE = 29;

	/// Global pulsewidth
	static const uint8_t PULSE_WIDTH = 30;

	/// Attack time
	static const uint8_t ATTACK_TIME   = 73;
	/// Decay time
	static const uint8_t DECAY_TIME    = 74;
	/// Sustain level
	static const uint8_t SUSTAIN_LEVEL = 75;
	/// Release time
	static const uint8_t RELEASE_TIME  = 76;

	/// Enable/disable the arpeggiator effect
	static const uint8_t ENABLE_ARPEGGIATOR     = 77;
	/// Amount of time one arpeggio takes
	static const uint8_t ARPEGGIO_TIME          = 78;
	/// Minimum number of notes needed to trigger an arpeggio
	static const uint8_t MINIMUM_ARPEGGIO_NOTES = 79;
	/// Direction arpeggio travels in (forward, reverse or random)
	static const uint8_t ARPEGGIO_DIRECTION     = 80;

	/// Store the current settings in the slot of the currently selected preset
	static const uint8_t SAVE_PRESET = 102;
};

#endif

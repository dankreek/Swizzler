/** @file SoundDriver.h
 *  @date Jul 20, 2010
 */
#ifndef SOUNDDRIVER_H_
#define SOUNDDRIVER_H_

#include <inttypes.h>
#include "Wire.h"

/**
 * Direct programming interface to the Swizzler Sound chip.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class SoundDriver {
public:

	// TODO - remove twi stuff, chip works in serial mode now
	/**
	 * @brief Create a new driver to a Swizzler sound chip.
	 *
	 * @param twiAddress	i2c (or two wire) address for the sound chip
	 */
	SoundDriver(uint8_t twiAddress);

	/**
	 * The different types of waveforms that the VCO's can produce
	 */
	enum WaveformType {
		triangleWave         = 0x00,	/*!< (0) Triangle wave */
		sawtoothWave         = 0x01,	/*!< (1) Sawtooth wave */
		reverseSawtoothWave  = 0x02,	/*!< (2) Reverse sawtooth wave */
		squareWave           = 0x03,	/*!< (3) Square wave */
		noiseWave            = 0x04		/*!< (4) Noise (not currently supported) */
	};

	/**
	 * @brief Reset every parameter on the sound chip
	 */
	void reset();

	// TODO - Make sure the level range is documented correctly
	/**
	 * @brief Set the level for a VCO.
	 *
	 * @param voiceNum	VCO number to set (0-3)
	 * @param level		The volume level to set (0 is silent, 0x7f is the loudest)
	 */
	void setVoiceLevel(uint8_t voiceNum, uint8_t level);

	/**
	 * @brief Set the wave form for a voice.
	 *
	 * @param voiceNum VCO number to set (0-3)
	 * @param waveform The waveform type
	 */
	void setWaveform(uint8_t voiceNum, WaveformType waveform);

	/**
	 * @brief Set the current frequency for a VCO
	 *
	 * @param voiceNum	VCO number to set (0-3)
	 * @param frequency	The frequency (in hz) to set
	 */
	void setFrequency(uint8_t voiceNum, uint16_t frequency);

	/**
	 * @brief Set the pulse width for one VCO's square waveform
	 *
	 * @param voiceNum	VCO number to set (0-3)
	 * @param pw		Duty cycle for square wave (0 = all low, 0xff = all high)
	 */
	void setPuleseWidth(uint8_t voiceNum, uint8_t pw);

	/**
	 * @brief Set the pulse width for every VCO on the sound chip.
	 *
	 * @param pw Duty cycle for square wave (0 = all low, 0xff = all high)
	 */
	void setGlobalPulseWidth(uint8_t pw);

	/**
	 * @brief Set the attack time of the envelope generator
	 *
	 * @param time	Attack time of envelope in ms
	 */
	void setAttackTime(uint16_t time);

	/**
	 * @brief Set the decay time of the envelope generator
	 *
	 * @param time	Decay time of envelope in ms
	 */
	void setDecayTime(uint16_t time);

	/**
	 * @brief Set the sustain level of the envelope generator
	 *
	 * @param level	Sustain level (0 = silent, 255 = max level)
	 */
	void setSustainLevel(uint8_t level);

	/**
	 * @brief Set the release time of the envelope generator
	 *
	 * @param time	Release time of envelope in ms
	 */
	void setReleaseTime(uint16_t time);

	/**
	 * @brief Open or close the envelope generator gate.
	 *
	 * The envelope generator starts the attack-decay-sustain phase when the gate is closed,
	 * and starts the release phase when the gate is open. Essentially the gate is closed for
	 * as long as a user has a key held down.
	 *
	 * @param isClosed True to close the gate, false to open it
	 */
	void setEnvelopeGate(bool isClosed);

	/**
	 * @brief Open then immediately close the envelope gate.
	 */
	void restartGate();

private:
	/**
	 *  i2c bus address of the sound chip
	 *  @todo Remove this, i2c is no longer used for sound chip communication
	 */
	uint8_t _twiAddress;
};

#endif

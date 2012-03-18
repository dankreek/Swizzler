/** @file SetParameters.h
 *  @date Mar 9, 2010
 */

#ifndef SETPARAMETERS_H_
#define SETPARAMETERS_H_

#include "Swizzler.h"

/**
 * @brief The service responsible for setting synth parameters based upon MIDI controller values
 *
 * All methods in this class take a 7bit unsigned int as an input which is the
 * size that a MIDI controller provides. (This makes patch
 * storing and loading much smaller).
 *
 * All scaling of controller values to real parameter values are done in these methods.
 */
class SetParameters {
public:
	/**
	 * @brief Enable/disable portamento.
	 *
	 * If \p ccValue >= 64 then enable portamento, otherwise disable it.
	 *
	 * @param ccValue	MIDI controller value.
	 */
	static void enablePortamento( uint8_t ccValue );
	/**
	 * @brief Set the amount of time between note glides if portamento is on.
	 *
	 * The actual glide time is decided by portTimeKnee. The range is between 0 and 2000ms.
	 *
	 * @param ccValue	MIDI controller value.
	 */
	static void setPortamentoTime( uint8_t ccValue );

	/**
	 * @brief Set the frequency of the LFO used for modulation effects.
	 *
	 * The actual frequency in hz is the \p ccValue divided by 4.
	 *
	 * @param ccValue	MIDI controller value.
	 */
	static void setLfoFreq( uint8_t ccValue );
	/**
	 * @brief Sets which parameter is modulated by the LFO.
	 *
	 * If \p ccValue is equal to
	 * LfoController::frequencyModulation (0) then the LFO modulates the output
	 * frequency, otherwise LfoController::pulsewidthModulation (1) then the LFO
	 * modulates each VCO's pulse width parameter. If \p ccValue is any other
	 * value then the command is ignored.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setLfoModulationParameter( uint8_t ccValue );

	/**
	 * @brief Sets the pulse width of the square wave for each VCO.
	 *
	 * 0 is the lowest duty cycle, 127 is the highest.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setPulseWidth( uint8_t ccValue );

	/**
	 * @brief Set the attack time of the envelope.
	 *
	 * The actual value is determined by
	 * \p attackTimeKnee. The range is between 0 and 4000ms
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setAttackTime( uint8_t ccValue );
	/**
	 * @brief Set the decay time of the envelope.
	 *
	 * The decay time value is determined by
	 * \p decRelTimeKnee. The range is between 0 and 24,000ms.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setDecayTime( uint8_t ccValue );
	/**
	 * @brief Sets the sustain level for the envelope.
	 *
	 * 0 would be a completely silent sustain and 127 is full volume.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setSustainLevel( uint8_t ccValue );
	/**
	 * @brief Set the release time of the envelope.
	 *
	 * The release time value is determined by \p decRelTimeKnee. The range is between 0 and 24,000ms.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setReleaseTime( uint8_t ccValue );

	/**
	 * @brief Sets the output level of VCO1.
	 *
	 * 0 is silence, 127 is full volume.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscLevel1( uint8_t ccValue );
	/**
	 * @brief Set the waveform for VCO1.
	 *
	 * \p ccValue can be one of the following values:
	 *
	 * \li SoundDriver::triangleWave
	 * \li SoundDriver::sawtoothWave
	 * \li SoundDriver::reverseSawtoothWave
	 * \li SoundDriver::squareWave
	 *
	 * If \p ccValue is not one of these values, then the command is ignored.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscWaveform1( uint8_t ccValue );

	/**
	 * @brief Sets the output level of VCO2.
	 *
	 * 0 is silence, 127 is full volume.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscLevel2( uint8_t ccValue );
	/**
	 * @brief Set the waveform for VCO2.
	 *
	 * \p ccValue can be one of the following values:
	 *
	 * \li SoundDriver::triangleWave
	 * \li SoundDriver::sawtoothWave
	 * \li SoundDriver::reverseSawtoothWave
	 * \li SoundDriver::squareWave
	 *
	 * If \p ccValue is not one of these values, then the command is ignored.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscWaveform2( uint8_t ccValue );
	/**
	 * @brief Set the frequency offset of VCO2.
	 *
	 * The frequency offset is measures in half-steps above or below the root note
	 * being played on the keyboard (or generated by the ArpeggiatorNoteFilter). The
	 * effective frequency offset is determined by \p ccValue / 4 - 16.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscOffset2( uint8_t ccValue );

	/**
     * @brief Sets the output level of VCO3.
     *
     * 0 is silence, 127 is full volume.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscLevel3( uint8_t ccValue );
	/**
	 * Set the waveform for VCO3. \p ccValue can be one of the following values:
	 *
	 * \li SoundDriver::triangleWave
	 * \li SoundDriver::sawtoothWave
	 * \li SoundDriver::reverseSawtoothWave
	 * \li SoundDriver::squareWave
	 *
	 * If \p ccValue is not one of these values, then the command is ignored.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscWaveform3( uint8_t ccValue );
	/**
	 * @brief Set the frequency offset of VCO2.
	 *
	 * The frequency offset is measures in half-steps above or below the root note
	 * being played on the keyboard (or generated by the ArpeggiatorNoteFilter). The
	 * effective frequency offset is determined by \p ccValue / 4 - 16.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setOscOffset3( uint8_t ccValue );

	/**
	 * @brief Enable/disable the arpeggio generator.
	 *
	 * If \p ccValue >= 64 then enable the arpeggiator, otherwise disable it.
	 *
	 * @param ccValue	MIDI controller value
	 *
	 * @see ArpeggioNoteFilter
	 */
	static void enableArpeggio( uint8_t ccValue );
	/**
     * @brief Set the arpeggio time
     *
     * The arpeggio time is the amount of time between notes in an arpeggio.
     * The time is a function of the value generated by \p arpTimeKnee + 10. Adding
     * 10 ms is done to prevent too fast of an arpeggio, which would bog down the
     * processor.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setArpeggioTime( uint8_t ccValue );
	/**
	 * @brief Set the minimum number notes required to start an arpeggio.
	 *
	 * No notes will play until the keyboard has more than the minimum number of
	 * notes are played at one time. The minimum number of notes is equal to
	 * \f$ \frac{ccValue}{32} + 1\f$ .
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setArpeggioMinNotes( uint8_t ccValue );
	/**
	 * @brief Set the direction in which the arpeggio will travel.
	 *
	 * The direction is equal to the constants defined in ArpeggiatorNoteFilter::ArpeggioDirection.
	 *
	 * @todo There is no default behavior defined, this needs to be fixed.
	 * @param ccValue	MIDI controller value
	 */
	static void setArpeggioDirection( uint8_t ccValue );

	/**
	 * @brief Set the range of the bend wheel.
	 *
	 * The range is measured in half steps +/- the root note. The pitch
	 * bend wheel will alter the pitch by that many half steps when it
	 * is pushed all the way forward or pulled all the way back.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setBendRange( uint8_t ccValue );

	/**
	 * @brief Set the modulation wheel level.
	 *
	 * The modulation wheel level determines the depth of the currently
	 * selected LFO effect.
	 *
	 * @param ccValue	MIDI controller value
	 */
	static void setModWheelLevel( uint8_t ccValue );

private:
	/**
	 * Return a point to either the "On" or "Off" string help in EEPROM based upon a boolean value.
	 *
	 * @param  onOff True if the desired string is "On", False if the desired string is "Off".
	 * @return Pointer to the desired string in EEPROM.
	 */
	static char* _onOffStr( bool onOff );

	/**
	 * Set the waveform of the specified VCO and update display.
	 *
	 * @param voiceNumber	VCO number to set waveform for. 0 = Triangle, 1 = Sawtooth, 2 = Reverse Sawtooth, 3 = Square (pulse)
	 * @param ccValue		MIDI controller value (1-4)
	 */
	static void    _setWaveform( uint8_t voiceNumber, uint8_t ccValue );

	/**
	 * Set the level of the specified VCO and update the display.
	 *
	 * @param voiceNumber	VCO number to set waveform for. 0 = Triangle, 1 = Sawtooth, 2 = Reverse Sawtooth, 3 = Square (pulse)
	 * @param ccValue		MIDI controller value (1-4)
	 */
	static void  _setVoiceLevel( uint8_t voiceNumber, uint8_t ccValue );

	/**
	 * Set the note offset of the specified VCO and update the display.
	 *
	 * @param voiceNumber	VCO number to set waveform for. 0 = Triangle, 1 = Sawtooth, 2 = Reverse Sawtooth, 3 = Square (pulse)
	 * @param ccValue		MIDI controller value (1-4)
	 */
	static void _setVoiceOffset( uint8_t voiceNumber, uint8_t ccValue );
};

#endif /* SETPARAMETERS_H_ */

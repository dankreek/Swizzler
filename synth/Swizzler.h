/** @file Swizzler.h
 *  @date Jan 31, 2010
 */

#ifndef SWIZZLER_H_
#define SWIZZLER_H_

#include "MidiInput.h"
#include "Wire.h"
#include "SetParameters.h"
#include "SurfaceControlManager.h"
#include "SoundDriver.h"
#include "ArpeggiatorNoteFilter.h"
#include "Oscillators.h"
#include "LfoController.h"
#include "FreqFilterChain.h"

/**
 * This class contains the main loop, and stores a lot of the core services and parameters
 * for the Swizzler synth.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class Swizzler {
public:
  /// The swizzler's LFO controller, which includes a sine wave generator
  static LfoController lfoController;

  /**
   * @brief The frequency filter chain which contains all the frequency modulation effects.
   *
   * These effects are portamento, LFO-modulated frequency modulation, and pitch bend.
   */
  static FreqFilterChain freqModEffectChain;

  /**
   * @brief The arpeggio note effect.
   *
   * This is the only note filter effect used.
   */
  static ArpeggiatorNoteFilter arp;

  /// Current level that the mod wheel is at (set by MidiInput)
  static uint8_t modWheelLevel;

  /**
   * Calculates the actual frequency of each VCO based on the note offset and the 
   * current frequency modulation level.
   */
  static Oscillators oscillators;
 
  // TODO - Figure out what this is measured in
  /// The amount of glide time between notes 
  static uint16_t portamentoTime;

  /// The current pitch bend range (measured in schlips - like cents but 32 divisions instead of 100 between half-steps)
  static int16_t bendRange;

  /// Incremented once every millisecond
  static uint16_t msCounter; 

  // TODO - Is this actually used anymore?
  /// Pin number that the LED is connected to
  static const int ledPin = 13;

  // TODO - This should be moved to SoundDriver
  /// The number of VCO's available on the sound chip
  static const uint8_t numOscillators = 3;

  /// Constains all the sound chip functionality
  static SoundDriver soundChip;

  /// This method is called any time MidiInput recieves a pitch bend message
  static void handlePitchBend();

  /// Initialize the all of the Swizzler's software
  void init();

  /// The main loop from whence we never leave
  void mainLoop();

  /// Turn the arpeggiator effect on or off
  static void enableArpeggio(bool onOff);

  /// Send the processor into an infinite blinking loop to indicate a run-time error
  static void setErrorState();

  /// Turn the indicator LED on or off
  static void setLed(bool onOff);
private:
  /// How long to wait until the display unit is fully powered up (measured in milliseconds)
  static const uint8_t  poweronDisplayDelay = 100;
};

extern Swizzler swizzler;

#endif /* SWIZZLER_H_ */


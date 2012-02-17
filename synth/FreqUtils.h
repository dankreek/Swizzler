/** @file FreqUtils.h
 *  @date Aug 29, 2010
 */

#ifndef FREQUTILS_H_
#define FREQUTILS_H_

#include <inttypes.h>

/**
 * A couple of utility classes used to calculate frequencies.
 *
 * Note the use of the term "schlips." This is a unit of measure I completely made up
 * to make frequency modulation easy without a floating point processor. A schlip is a linear division of
 * 1/32nd of the distance between notes. Most normal people would use the common measurement
 * of cents, but this processor's just too weenie to calculate a logarithmic value like that.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class FreqUtils {
public:
  /**
   * Calculate a frequency from a MIDI note number
   *
   * @param noteNum		MIDI note number
   * @return 			The frequency of the MIDI note
   */
  static uint16_t noteToFreq(uint8_t noteNum);

  /**
   * Modulate the base frequency up or down by the number of schlips. What's a schlip?
   * Well it's just like a cent, only instead of 100 divisions between half steps
   * there's 32. And instead of the divisions being logarithmic, they're linear.
   *
   * @param basenote	The MIDI note number used to calculate the base frequency
   * @param numSchlips	The number of schlips to modulate that note. Negative numbers modulate the frequency
   *                    down, positive ones up.
   * @return The frequency of the base MIDI number modulated by \p numSchlips
   */
  static uint16_t modulatedFreq(uint8_t basenote, int16_t numSchlips);

  /// Number of divisions between half-steps determining one schlip
  static const uint8_t schlipsDivs = 32;

private:
  /**
   * Frequency -> Note lookup table. These are the frequencies for
   * the 8th octave. All the frequencies for the lower frequencies are
   * found by dividing.
   */
  static uint16_t noteLookupTable[];


};

#endif /* FREQUTILS_H_ */

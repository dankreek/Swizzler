/** @file SineTable.h
 *  @date Oct 2, 2010
 */

#ifndef SINETABLE_H_
#define SINETABLE_H_

#include <inttypes.h>

/**
 * Class used to generate an entire sine wave table out of the first 1/4 of the wave.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class SineTable {
public:
  /**
   * @brief Get the value of the sine wave
   *
   * @param phase The phase of the sine wave. ( 0 - SINE_WAVE_TABLE_LENGTH-1 )
   * @return The sine wave value (-255 to 255)
   */
  int16_t getSine(uint16_t phase);

private:
  static const uint8_t SINE_TABLE_DIVISIONS = 32;

  /// Length of the 1/4 sine wave
  static const uint8_t SINE_TABLE_LENGTH = SINE_TABLE_DIVISIONS+1;

  // TODO Put the math in the actual constant declaration
  /// Length of the entire derived sine table, SINE_TABLE_DIVISIONS * 4
  static const uint8_t SINE_WAVE_TABLE_LENGTH = 128;

  /// The hard-coded 1/4 sine wave table
  static uint8_t _sineTable[SINE_TABLE_LENGTH];
};

#endif /* SINETABLE_H_ */

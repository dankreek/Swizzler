/** @file SineGenerator.h
 *  @date Oct 3, 2010
 */

#ifndef SINEGENERATOR_H_
#define SINEGENERATOR_H_

#include <inttypes.h>
#include "ITimerCall.h"
#include "SineTable.h"

/**
 * Generates a sine wave of a set frequency using a 1/4 sine table and the timer.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class SineGenerator : public ITimerCall  {
public:
  SineGenerator();

  /**
   * @brief Sets the frequency of the sine wave.
   *
   * The actual frequency range available is 0-32hz, but this method accepts a
   * value 8 times larger than the actual frequency in order to allow for a fractional
   * frequency.
   *
   * The actual frequency value is \f$ \frac{freq}{8}\mbox{hz} \f$.
   *
   * @param freq The sine wave frequency. Actual value in hz is equal to freq/8
   */
  void setFrequency(uint16_t freq);

  void nextTick();

  /**
   *  @brief Get the current sine value
   *
   *  @return Current sine value (between -255 and 255 inclusive)
   */
  int16_t getCurValue();

private:
  SineTable _sineTable;

  /// Amount to increment the accumulator by on each timer tick
  uint16_t _incAmount;

  /// Accumulator which is used to determine the current phase of the sine wave
  uint16_t _idxAccum;
};

#endif /* SINEGENERATOR_H_ */

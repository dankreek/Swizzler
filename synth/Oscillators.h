/*
 * Oscillators.h
 *
 *  Created on: Aug 28, 2010
 *      Author: justin
 *
 *
 * This class takes the root note that's been played on the keyboard and
 * sends it to each of the 3 oscillator's frequency filters.
 */

#ifndef OSCILLATORS_H_
#define OSCILLATORS_H_

#include "ANoteReceiver.h"
#include "FreqFilterChain.h"

class Oscillators : public ANoteReceiver {
public:
  Oscillators();
  void noteOn(uint8_t noteNum, uint8_t velocity);
  void noteOff(uint8_t noteNum);

  /**
   * Set an oscillator's note offset
   */
  void setNoteOffset(uint8_t oscNum, int8_t offset);

  // The number of voices with frequency (voice 4 is only white noise)
  static const uint8_t numVoices = 3;

private:
  FreqFilterChain oscillatorList[numVoices];
};



#endif /* OSCILLATORS_H_ */

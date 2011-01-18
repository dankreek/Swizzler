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
#include "ITimerCall.h"

class Oscillators : public ANoteReceiver {
public:
  Oscillators();
  void noteOn(uint8_t noteNum, uint8_t velocity);
  void noteOff(uint8_t noteNum);

  // Set an oscillator's note offset
  void setNoteOffset(uint8_t oscNum, int8_t offset);

  // Signal an update to all oscillators
  void update();

  // The number of voices with frequency (voice 4 is only white noise)
  static const uint8_t numVoices = 3;

private:
  uint8_t curRootNote;

//  FreqFilterChain oscillatorList[numVoices];
  int8_t noteOffset[numVoices];

  // Keep track of the last frequency output so no redundant frequency is sent to the sound chip
  uint16_t lastFreq[numVoices];

  // Calculate the frequency and send out to the sound chip
  void outputFrequency(uint8_t voiceNum);
};

#endif /* OSCILLATORS_H_ */

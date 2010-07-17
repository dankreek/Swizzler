/*
 * PwmOut.h
 *
 *  Created on: Jul 10, 2010
 *      Author: justin
 */

#ifndef PWMOUT_H_
#define PWMOUT_H_

#include <inttypes.h>

class PwmOut {
public:
  // The current sample rate at which digital audio is mixed
  static const uint16_t sampleRate=16000;

  // Initialize the PWM output
  static void init();
};

#endif /* PWMOUT_H_ */

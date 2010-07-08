/*
 * DisplayOutput.h
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#ifndef DISPLAYOUTPUT_H_
#define DISPLAYOUTPUT_H_

#include "DisplayOutput.h"
#include "Swizzler.h"
#include <inttypes.h>
#include <stdio.h>

class DisplayOutput {
public:
  /**
   * Initialize the display unit and show the power-on greeting
   */
  static void init();

  static inline
  void putChar(uint8_t c) {
    Wire.beginTransmission(twiAddress);
    Wire.send(c);
    Wire.endTransmission();
  }
private:
  static const uint8_t twiAddress = 0x69;
};

#endif /* DISPLAYOUTPUT_H_ */

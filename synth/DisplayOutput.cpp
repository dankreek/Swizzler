/*
 * DisplayOutput.cpp
 *
 *  Created on: Jul 7, 2010
 *      Author: justin
 */

#include "DisplayOutput.h"
#include "Swizzler.h"
#include <stdio.h>

void DisplayOutput::init() {
  /*
  Wire.beginTransmission(0x69);
  Wire.send('!');
  Wire.endTransmission();
  */

}

void DisplayOutput::print(char s[]) {
  char* c;

  Wire.beginTransmission(twiAddress);
  for (c=s; *c; c++) {
    Wire.send(*c);
  }
  Wire.endTransmission();
}

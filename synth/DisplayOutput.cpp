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
  //printf("Welcome to swizzler");
  Wire.beginTransmission(0x69);
  Wire.send('!');
  Wire.endTransmission();

}

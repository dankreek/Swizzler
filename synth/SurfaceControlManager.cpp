/*
 * SurfaceControlManager.cpp
 *
 *  Created on: Jul 4, 2010
 *      Author: justin
 */

#include "SurfaceControlManager.h"
#include "DisplayDriver.h"
#include <avr/eeprom.h>

DisplayFrameBuffer SurfaceControlManager::displayOut;

uint8_t EEMEM greetingString1[] = "Welcome To";
uint8_t EEMEM greetingString2[] = "Swizzler";

void SurfaceControlManager::init() {
  DisplayDriver::init();
}

void SurfaceControlManager::displayGreeting() {
  displayOut.clear();
  displayOut.writeEepromString(greetingString1, 0, 3);
  displayOut.writeEepromString(greetingString2, 1, 4);
}

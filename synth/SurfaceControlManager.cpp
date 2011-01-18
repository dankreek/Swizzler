/*
 * SurfaceControlManager.cpp
 *
 *  Created on: Jul 4, 2010
 *      Author: justin
 */

#include "SurfaceControlManager.h"
#include "DisplayOutput.h"

DisplayFrameBuffer SurfaceControlManager::displayOut;

uint8_t EEMEM greetingString1[] = "Welcome To";
uint8_t EEMEM greetingString2[] = "Swizzler";

void SurfaceControlManager::init() {
  DisplayOutput::init();
  displayOut.writeEepromString(greetingString1, 0, 3);
  displayOut.writeEepromString(greetingString2, 1, 4);
}

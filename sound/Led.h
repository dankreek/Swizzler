/*
 * Led.h
 *
 *  Created on: Nov 13, 2010
 *      Author: justin
 */

#ifndef LED_H_
#define LED_H_

class Led
{
public:
  static void init();
  static void setLedOn(bool onOff);
  static void toggleLed();
};

#endif /* LED_H_ */

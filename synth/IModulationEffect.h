/*
 * IModulationEffect.h
 *
 *  Created on: Jan 5, 2011
 *      Author: justin
 */

#ifndef IMODULATIONEFFECT_H_
#define IMODULATIONEFFECT_H_

class IModulationEffect {
public:
  /**
   * Next modulation value (-255 to 255)
   */
  virtual void nextModulationValue(int16_t value) = 0;

  virtual void enableEffect(bool onOff) = 0;
};

#endif /* IMODULATIONEFFECT_H_ */

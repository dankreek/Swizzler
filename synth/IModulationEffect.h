/** @file IModulationEffect.h
 *  @date Jan 5, 2011
 */

#ifndef IMODULATIONEFFECT_H_
#define IMODULATIONEFFECT_H_

/**
 * This is an interface defining the behaviour of a modulation effect.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class IModulationEffect {
public:
  /**
   * Set the modulation level for this effect. Can be in the range from -255 to 255
   * which is the range of values given by most MIDI modulation wheels, adjusted for signedness. 
   * Although the MIDI spec states that the modulation value is a 14 bit number from 0 to 16383
   *
   * @param value   The next modulation value [-255, 255]
   */
  virtual void nextModulationValue(int16_t value) = 0;

  /**
   * Turn the effect on or off
   *
   * @param onOff   True to turn the effect on, false to bypass the effect.
   */
  virtual void enableEffect(bool onOff) = 0;
};

#endif /* IMODULATIONEFFECT_H_ */

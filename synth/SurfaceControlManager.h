/** @file SurfaceControlManager.h
 *  @date Jul 4, 2010
 */

#ifndef SURFACECONTROLMANAGER_H_
#define SURFACECONTROLMANAGER_H_

#include "DisplayFrameBuffer.h"

/**
 * This utility class handles interacting with the display, keypad and pots on the surface.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class SurfaceControlManager {
public:
  /**
   * Initialize all of the surface controls. Currently just the display.
   */
  static void init();

  /**
   * Output the power-on greeting to display 
   */
  static void displayGreeting();

  /**
   * Frame buffer for output display.
   */
  static DisplayFrameBuffer displayOut;
};

#endif /* SURFACECONTROLMANAGER_H_ */

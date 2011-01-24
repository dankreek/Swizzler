/*
 * SurfaceControlManager.h
 *
 *  Created on: Jul 4, 2010
 *      Author: justin
 */

#ifndef SURFACECONTROLMANAGER_H_
#define SURFACECONTROLMANAGER_H_

#include "DisplayFrameBuffer.h"

class SurfaceControlManager {
public:
  /**
   * Initialize the surface controls
   */
  static void init();

  // Output the power-on greeting
  static void displayGreeting();

  // Frame buffer for output display
  static DisplayFrameBuffer displayOut;
private:
};

#endif /* SURFACECONTROLMANAGER_H_ */

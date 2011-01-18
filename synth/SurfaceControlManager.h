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

  // Frame buffer for output display
  static DisplayFrameBuffer displayOut;
private:
};

#endif /* SURFACECONTROLMANAGER_H_ */

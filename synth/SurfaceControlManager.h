/*
 * SurfaceControlManager.h
 *
 *  Created on: Jul 4, 2010
 *      Author: justin
 */

#ifndef SURFACECONTROLMANAGER_H_
#define SURFACECONTROLMANAGER_H_

#include "DisplayOutput.h"

class SurfaceControlManager {
public:
  /**
   * Initialize the surface controls
   */
  static void init();

  static DisplayOutput output;
private:
};

#endif /* SURFACECONTROLMANAGER_H_ */

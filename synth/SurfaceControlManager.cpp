/*
 * SurfaceControlManager.cpp
 *
 *  Created on: Jul 4, 2010
 *      Author: justin
 */

#include "SurfaceControlManager.h"
#include "DisplayOutput.h"

DisplayOutput SurfaceControlManager::output;

void SurfaceControlManager::init() {
  DisplayOutput::init();
}

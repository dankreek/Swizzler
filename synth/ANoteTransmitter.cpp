/*
 * ANoteTransmitter.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#include "ANoteTransmitter.h"

void ANoteTransmitter::linkTo(ANoteReceiver *recv) {
  receiver = recv;
}


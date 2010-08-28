/*
 * ANoteTransmitter.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: justin
 */

#include "ANoteTransmitter.h"

ANoteReceiver* ANoteTransmitter::linkTo(ANoteReceiver *recv) {
  receiver = recv;
  return recv;
}


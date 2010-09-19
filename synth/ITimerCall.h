/*
 * ITimerCall.h
 *
 *  Created on: Sep 18, 2010
 *      Author: justin
 */

#ifndef ITIMERCALL_H_
#define ITIMERCALL_H_

class ITimerCall {
public:
  // This method is called every ms by the timer
  virtual void nextTick() = 0;

};

#endif /* ITIMERCALL_H_ */

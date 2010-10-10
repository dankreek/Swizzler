/*
 * TimerService.cpp
 *
 *  Created on: Oct 9, 2010
 *      Author: justin
 */

#include "TimerService.h"

TimerService::TimerService(uint8_t interval, ITimerCall *call) {
  timerInterval = interval+1;
  callback = call;
  curTime = interval;
}

void TimerService::nextMs() {
  curTime--;

  if (curTime == 0) {
    callback->nextTick();
    curTime = timerInterval+1;
  }
}

void TimerService::executeServices(TimerService* serviceList[]) {
  // Loop through each TimerService in the provided array until a null pointer is found
  for (uint8_t i=0; serviceList[i]->callback != (void*)0; i++) {
    serviceList[i]->nextMs();
  }
}

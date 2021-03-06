/** @file TimerService.h
 *  @date Oct 9, 2010
 */

#ifndef TIMERSERVICE_H_
#define TIMERSERVICE_H_

#include <inttypes.h>
#include "ITimerCall.h"

/**
 * This class represents one timer service. This is currently
 * not being used, but it may be a good idea to implement this.
 *
 * TODO - Implement this?
 *
 * @author Justin May <may.justin@gmail.com>
 */
class TimerService {
public:
  /**
   * Create a new TimerService that fires the callback at *call every interval+1 milliseconds
   */
  TimerService(uint8_t interval, ITimerCall *call);

  /**
   * Decrement the curTime. If curTime is zero, fire the callback and reset the timer.
   */
  void nextMs();

  /**
   * Loop through a list of services and execute each one's nextMs() method.
   * The list is terminated by a null call pointer
   */
  static void executeServices(TimerService* serviceList[]);

  ITimerCall* callback;
private:
  // Counts down from timerInterval to 0 once every millisecond
  uint8_t curTime;

  // How often this service is fired. (every timerInterval+1 milliseconds)
  uint8_t timerInterval;
};

#endif /* TIMERSERVICE_H_ */

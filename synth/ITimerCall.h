/** @file ITimerCall.h
 *  @date Sep 18, 2010
 */

#ifndef ITIMERCALL_H_
#define ITIMERCALL_H_

/**
 * Interface defining the behaviour of a class which needs to be serviced by the timer.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class ITimerCall {
public:
  /**
   * This method is called every timer tick
   * TODO - Is this still true? I think different services are called at different intervals now.
   */
  virtual void nextTick() = 0;

protected:
  ~ITimerCall();
};

inline ITimerCall::~ITimerCall() {}

#endif /* ITIMERCALL_H_ */

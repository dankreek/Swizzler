/*
 * InputHandler.h
 *
 *  Created on: Jul 17, 2010
 *      Author: justin
 *
 *  The sound chip's command format works as such:
 *
 *  The first byte is either a 0, which signifies a command that has a global effect
 *  on the chip, or a number 1-8 which signifies a command that has an effect on a
 *  particular voice. All the commands available are as follows:
 *
 *  Global Commands:
 *  ================
 *
 *  Set output volume: 0x00 0x00 <volume>
 *  ------------------
 *  Sets the master output volume of the sound chip, where <volume>==0x00 is complete silence
 *  and 0xff is the loudest possible volume. Default is 0xff.
 *
 *  Set filter cutoff frequency: 0x00 0x01 <cutoff>
 *  ----------------------------
 *
 *  Voice Commands:
 *  ===============
 *
 *  Set voice volume: <voice number> 0x00 <volume>
 *  -----------------
 *  Sets the output volume of the voice where 0x00 is completely silent and 0xff is fully loud.
 *
 *  Set voice waveform: <voice number> 0x01 <waveform type>
 *  -------------------
 *  Change the waveform of the voice to one of the following waveform types:
 *
 *  0x00 = Triangle wave
 *  0x01 = Square wave
 *  0x02 = Sawtooth
 *  0x03 = Noise (random)
 *
 *  Set voice's square pulse width: <voice number> 0x02 <pulse width high byte> <pulse width low byte>
 *  -------------------------------
 *  Sets the pulse width of the square wave, can be a number between 0x0000 and 0xffff
 *  which signifies the duty cycle of the square wave form. 0x0000 would mean a wave that
 *  is always low, 0xffff would be a wave that's always high, and 0x8000 would be a totally
 *  Symmetrical square wave.
 *
 *  Set voice attack speed: <voice number> 0x03 <attack speed high byte> <attack speed low byte>
 *  -----------------------
 *  Sets the speed of the attack phase of the envelope generator. Which would be the time
 *  starting from when the gate if first closed going to when the envelop reaches max
 *  level. Attack speed is specified in milliseconds.
 *
 *  Set voice decay speed: <voice number> 0x04 <decay speed high byte> <decay speed low byte>
 *  ----------------------

 *  Set voice sustain level: <voice number> 0x05 <sustain level>
 *  ------------------------

 *  Set voice release speed: <voice number> 0x06 <release speed high byte> <release speed low byte>
 *  -----------------------
 *
 *  Set voice's envelope gate state: <voice number> 0x07 <gate state>
 *  --------------------------------
 *
 *  Turn filter on/off for a voice: <voice number> 0x08 <filter on/off>
 *  -------------------------------
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <inttypes.h>

class InputHandler {
public:
  /**
   * Read in a byte from the input stream and interpret it
   */
  static void handleInput(uint8_t i);

  enum inputHandlerState { one, two };
};

#endif /* INPUTHANDLER_H_ */

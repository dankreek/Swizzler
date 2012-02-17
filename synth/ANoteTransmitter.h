/** @file   ANoteTransmitter.h
 *  @date   Aug 22, 2010
 *  @author Justin May <may.justin@gmail.com>
 */

#ifndef ANOTETRANSMITTER_H_
#define ANOTETRANSMITTER_H_

#include <inttypes.h>
#include "ANoteReceiver.h"

/**
 * Abstract class defining the behavior of class which sends MIDI notes to an ANoteReceiver.
 *
 * @see ANoteReceiver
 */
class ANoteTransmitter {

public:
  /**
   * Connect a note receiver to the output of this note transmitter
   *
   * @param noteReceiver    Pointer to the object that will be receiving note on/off commands
   */
  void linkTo( ANoteReceiver *noteReceiver );

  // TODO : sending notes should be private operations

  // The ANoteTansmitter interface allows a class to send a note to a note receiver

  /**
   * Send a "note on" message to the note reciever
   *
   * @param noteNumber  MIDI note number to send
   * @param velocity    The velocity level of the note
   */
  void sendNoteOn( uint8_t noteNumber, uint8_t velocity );

  /**
   * Send a "note off" message to the note receiver
   *
   * @param noteNumber  MIDI note number to signal off
   */
  void sendNoteOff( uint8_t noteNumber );

protected:

  /// Pointer to the class which receives the note
  ANoteReceiver *receiver;

  ~ANoteTransmitter();
};

inline
void ANoteTransmitter::linkTo( ANoteReceiver *recv ) {
  receiver = recv;
}

inline
void ANoteTransmitter::sendNoteOn(uint8_t noteNumber, uint8_t velocity) {
  receiver->noteOn( noteNumber, velocity );
}

inline
void ANoteTransmitter::sendNoteOff(uint8_t noteNumber) {
  receiver->noteOff( noteNumber );
}

inline ANoteTransmitter::~ANoteTransmitter() {}

#endif /* ANOTETRANSMITTER_H_ */

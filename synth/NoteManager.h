#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <inttypes.h>
#include "ANoteReceiver.h"
#include "ANoteTransmitter.h"

class NoteManager : public ANoteReceiver {
public:
  NoteManager();

  /**
   * Initialize the note manager
   */
  void init();

  /**
   * Signal that a note has been hit
   * @noteNumber	MIDI note number that has been hit
   */
  void noteOn(uint8_t noteNumber, uint8_t velocity);

  /**
   * Tell the frequency manager that a note has been let off
   */
  void noteOff(uint8_t noteNumber);

  // Called every millisecond to keep the arpeggios running
  void nextTick();

private:
  // Open then close the envelope gate again (new note is struck)
  void restartGate();
};

#endif

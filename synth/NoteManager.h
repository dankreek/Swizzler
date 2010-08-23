#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <inttypes.h>
#include "ArpManager.h"
#include "INoteReceiver.h"
#include "INoteTransmitter.h"

class NoteManager : public INoteReceiver {
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

  /**
   * Turn the arepggiator on or off
   * @onOff True: arpeggios on, False: arepggios off
   */
  void enableArpeggio(bool onOff);

  // Keeps track of arpeggio generation
  ArpManager arpManager;

  // Called every millisecond to keep the arpeggios running
  void nextTick();

private:
  // Is the arpeggiator on or off?
  bool arpOn;

  // Stop the arpeggiator, reload it, and start it up again
  void reloadArpeggiator();

  // Open then close the envelope gate again (new note is struck)
  void restartGate();
};

#endif

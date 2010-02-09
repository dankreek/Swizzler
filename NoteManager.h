#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <inttypes.h>
#include "ArpManager.h"
#include "FrequencyManager.h"

class NoteManager {
  public:
	/**
	 * Signal the a note has been hit
	 * @noteNumber	MIDI note number that has been hit
	 */
	static void noteOn(uint8_t noteNumber);

	/**
	 * Tell the frequency manager that a note has been let off
	 */
	static void noteOff(uint8_t noteNumber);
	
	/**
	 * Turn the arepggiator on or off
	 * @onOff True: arpeggios on, False: arepggios off
	 */
	static void enableArpeggio(bool onOff);
	
	// Keeps track of arpeggio generation
	static ArpManager arpManager;
	
	// Called every millisecond to keep the arpeggios running
	inline static void nextTick() {
		if (arpOn) {
			// If the arpmanager says we should send a new note
			if (arpManager.nextTick()) {
				// Send it
				FrequencyManager::newNote(arpManager.curNote());
			}
		}
	} 
	
  private:
  	// Is the arpeggiator on or off?
  	static bool arpOn;

  	// Stop the arpeggiator, reload it, and start it up again
	static void reloadArpeggiator();
	
	// Open then close the envelope gate again (new note is struck)
	static void restartGate();
};

#endif

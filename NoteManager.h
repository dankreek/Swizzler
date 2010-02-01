#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <inttypes.h>

class NoteManager {
  public:
	/**
	 * Signal the a note has been hit
	 * @noteNumber	MIDI note number that has been hit
	 */
	static
	void noteOn(uint8_t noteNumber);

	/**
	 * Tell the frequency manager that a note has been let off
	 */
	static
	void noteOff(uint8_t noteNumber);
};

#endif

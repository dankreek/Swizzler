#ifndef ARPMANAGER_H
#define ARPMANAGER_H

#include <inttypes.h>

#define ARP_BUFFER_SIZE	8

class ArpManager {
  public:
  	/**
  	 * The minimum number of notes needed to start an arpeggio
  	 */
  	uint8_t minNotes;
  
	/**
	 * Restart the arpeggio generator
	 */
	void restartArpeggio();

	/**
	 * This needs to be called once per millisecond (handled by timer interrup)
	 * 
	 * @return true if the next note in the sequence is triggered, 
	 *         false if still on current note
	 */
	bool nextTick();

	/**
	 * Time between note changes (milliseconds)
	 */
	uint16_t arpTime;

	/**
	 * MIDI notes in arpeggio generator
	 * Do NOT modify while generator is ticking 
	 */
	uint8_t noteList[ARP_BUFFER_SIZE];

	/**
	 * Size of the note list
	 * Do NOT modify while generator is ticking
	 */
	uint8_t noteListSize;

	/**
	 * index pointer to current note in arpeggio
	 */
	uint8_t noteListIndex;

	/**
	 * Macro to get the pointer to the current note
	 */
	inline uint8_t curNote() {
		return noteList[noteListIndex];
	}
	
	// Is an arpeggio currently running?
	bool arpRunning;
	
  private:
	/**
	 * Counts up to arpTime and switches to next note
	 */
	uint16_t arpCounter;
};

#endif

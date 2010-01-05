#ifndef ARPMANAGER_H
#define ARPMANAGER_H

#include <inttypes.h>

#define ARP_BUFFER_SIZE	8

class ArpManager {
  public:
	/**
	 * Restart the arpeggio generator
	 */
	void restartArpeggio();

	/**
	 * This needs to be called once per millisecond
	 * @return true if the next note in the sequence is triggered, 
	 *         false if still on current note
	 */
	bool nextTick();

	/**
	 * Time between note changes in milliseconds
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
  private:
	/**
	 * Counts up to arpTime and switches to next note
	 */
	uint16_t arpCounter;
};

#endif

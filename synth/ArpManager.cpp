#include "ArpManager.h"


void ArpManager::init() {
	minNotes = 2;
	arpTime = 50;
	noteListSize = 0;
}

void ArpManager::restartArpeggio() {
	// Set the note index to the last element so it will rollover on nextTick()
	noteListIndex = (noteListSize-1);

	// Set to the last tick so a rollover to 0 will occur on nextTick()
	arpCounter = (arpTime-1);
	
	arpRunning = true;
}

bool ArpManager::nextTick() {
	// If there is a buffer to be arp'ed
	if (noteListSize >= minNotes) {
		// Increment the counter to the next note
		arpCounter = (arpCounter + 1) % arpTime;

		if (arpCounter == 0) {
			noteListIndex = (noteListIndex + 1) % noteListSize;
			return true;
		}
		else {
			return false;
		}
	}
	else
		return false;
}



#include "ArpManager.h"

void ArpManager::restartArpeggio() {
	noteListIndex = 0;

	// Set to the last tick so a rollover to 0 will occur on nextTick()
	arpCounter = (arpTime-1);
}

bool ArpManager::nextTick() {
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



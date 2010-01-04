#include "ArpManager.h"

void ArpManager::restartArpeggio() {
	noteListIndex = 0;
	arpCounter = arpTime;
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



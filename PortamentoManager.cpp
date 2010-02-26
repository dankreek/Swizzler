#include "PortamentoManager.h"

void PortamentoManager::init() {
	prevFreq = -1;
	destFreq = -1;
	curFreq = -1;
	time = 100;
	done = true;	
}

void PortamentoManager::nextDirectFreq(uint16_t freq) {
	destFreq = freq;
	prevFreq = freq;
	done = false;
}

void PortamentoManager::nextGlideFreq(uint16_t freq) {
	prevFreq = destFreq;
	curFreq = prevFreq;
	destFreq = freq;
	done = false;
	timeLine.init(prevFreq, destFreq, time);
}

bool PortamentoManager::nextTick() {
	if (!done) {
		// If prev and dest are the same just go there directly
		if (destFreq == prevFreq) {
			curFreq = destFreq;
			done = true;
			return true;
		}
		else {
			int16_t nextFreq;
			bool stillGoing = timeLine.next(&nextFreq);

			if (!stillGoing) {
				curFreq = destFreq;
				done = true;
				return true;
			}
			else if (curFreq != nextFreq) {	
				curFreq = nextFreq;
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

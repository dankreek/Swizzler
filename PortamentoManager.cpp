#include "PortamentoManager.h"

void PortamentoManager::begin() {
	prevFreq = -1;
	destFreq = -1;
	curFreq = -1;
	time = 100;
	done = true;	
}

void PortamentoManager::nextFreq(uint16_t freq) {
	if (prevFreq == -1) {
		prevFreq = freq;
		destFreq = freq;
		done = true;
	}
	else {
		prevFreq = destFreq;
		destFreq = freq;
		done = false;
		timeLine.init(prevFreq, destFreq, time);
	}
}

bool PortamentoManager::nextTick() {
	if (!done) {
		int16_t nextFreq;
		bool lineDone = timeLine.next(&nextFreq);

		if (nextFreq != curFreq) {
			curFreq = nextFreq;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

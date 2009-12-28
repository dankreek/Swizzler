#include "AudioLine.h"

void AudioLine::begin(int amp1, int amp2, int time) {
	dAmp = amp2-amp1;
	dTime = time;
	iAmp = amp1;
}

int AudioLine::getAmp(int t) {
	return (dAmp*t)/dTime + iAmp;
}

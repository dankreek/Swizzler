#ifndef AUDIOLINE_H
#define AUDIOLINE_H

class AudioLine {
  public:
	// Setup a new amplitude line
	// The line will go from amplitude1 to amplitude2 in a duration of time ms
	void begin(int amp1, int amp2, int time);

	// Get the amplitude at time t
	int getAmp(int t);

  private:
	int dAmp;	// Amplitude delta
	int dTime;	// Line time in milliseconds
	int iAmp;	// The line's initial amplitude
};

#endif

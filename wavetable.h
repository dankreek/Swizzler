#ifndef WAVETABLE_H_
#define WAVETABLE_H_

#define TABLE_SIZE	16
#define WAVE_HEIGHT 16

class Wavetable {
  public:
	Wavetable();
	static void generateTriangle(unsigned char*);
	static void generateSawtooth(unsigned char*);
	static void generateNoise(unsigned char*);

	static unsigned char noise_wt[TABLE_SIZE];
	static unsigned char tri_wt[TABLE_SIZE];	
	static unsigned char saw_wt[TABLE_SIZE];
  private:
	int stank;
};

#endif /*WAVETABLE_H_*/

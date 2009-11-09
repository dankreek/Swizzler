#ifndef BRESENHAM_H
#define BRESENHAM_H

/**
 * This class implements Bresenham's algorithm (optimized for audio)
 */
class Bresenham {
    private:
	int diffX, diffY;
	int initY, plotY, unitY;
	int i, error_term;

    public:
	void init(int x1, int y1, int x2, int y2);
	void reset();

	// Get the next y-value in the line
	bool next(int *output);
};

#endif

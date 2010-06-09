#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <inttypes.h>


/**
 * This class implements Bresenham's algorithm (optimized for audio)
 *
 * This is essentially a fast way of computing a linear function incrementally
 */
class Bresenham {
    private:
	int16_t diffX, diffY;
	int16_t initY, plotY, unitY;
	int16_t i, error_term;

    public:
	void init(int16_t y1, int16_t y2, int16_t x2);
	void reset();

	// Get the next y-value in the line
	bool next(int16_t *output);
};

#endif

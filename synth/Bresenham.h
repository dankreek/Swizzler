#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <inttypes.h>


/**
 * This class implements Bresenham's algorithm (optimized for audio)
 *
 * This is essentially a fast and fairly accurate way of computing a linear function incrementally
 */
class Bresenham {
public:
  void init(int16_t y1, int16_t y2, int16_t x2);
  void reset();

  // Get the next y-value in the line
  void next(int16_t *output);

  // Is the line still going?
  bool stillGoing();
private:
  int16_t diffX, diffY;
  int16_t initY, plotY, unitY;
  int16_t count, error_term;

};

#endif

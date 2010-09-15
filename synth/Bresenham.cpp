#include "Bresenham.h"

void Bresenham::init(int16_t y1, int16_t y2, int16_t x2) {
  initY = y1;
  diffY = y2-y1;
  diffX = x2;

  if (diffY < 0) {
    diffY = -diffY;
    unitY = -1;
  }
  else
    unitY = 1;

  reset();
}

/**
 * Start the algorithm over again
 */
void Bresenham::reset() {
  plotY = initY;
  count = 0;
  error_term = 0;
}

/**
 * Calculate next value in the line using Bresenham's audio-enhanced algorithm/
 * @line Pointer to line struct to traverse
 * @output Pointer to the output of the next sample in the line
 * returns FALSE if this was the last sample in the line, or TRUE if there is still points left in the line
 */
void Bresenham::next(int16_t *output) {
  if (diffX >= diffY) {
    *output = plotY;
    error_term += diffY;

    if (error_term > diffX) {
      error_term -= diffX;
      plotY += unitY;
    }
    this->count++;
  }
  else {
    //int startY = this->plotY;
    for (; (error_term <= 0) && (count <= diffY); count++) {
      plotY += unitY;
      error_term += diffX;
    }
    error_term -= diffY;

    // Put the sample in the midpoint of the verticle line
    //*output = ((this->plotY + startY)/2);

    // Put the sample at the top of the verticle line
    *output = plotY;
  }

  if (!stillGoing()) *output = diffX;
}

bool Bresenham::stillGoing() {
  if (diffX >= diffY)
    return (count < diffX);
  else
    return (count <= diffY);
}


#include "bresenham.h"

void Bresenham::init(int x1, int y1, int x2, int y2) {
#ifdef DEBUG
	printf("Drawing line (%d, %d) - (%d, %d)\n", x1, y1, x2, y2);
#endif
	this->initY = y1;
 	this->diffY = y2-y1;
 	this->diffX = x2-x1;
 	
 	if (this->diffY < 0) {
 		this->diffY = -this->diffY;
 		this->unitY = -1;
 	}
 	else
 		this->unitY = 1;	
}

/**
 * Start the algorithm over again
 */
void Bresenham::reset() {
	this->plotY = this->initY;
	this->i = 0;
	this->error_term = 0;
}

/**
 * Calculate next value in the line using Bresenham's audio-enhanced algorithm/
 * @line Pointer to line struct to traverse
 * @output Pointer to the output of the next sample in the line
 * returns FALSE if this was the last sample in the line, or TRUE if there is still points left in the line
 */
bool Bresenham::next(int *output) {
	if (this->diffX >= this->diffY) {
		*output = this->plotY;
		this->error_term += this->diffY;
		
		if (this->error_term > this->diffX) {
			this->error_term -= this->diffX;
			this->plotY += this->unitY;
		}
		this->i++;
		
		if (this->i >= this->diffX)
			return false;
		else
			return true;
	}
	else {
		//int startY = this->plotY;
		for (; (this->error_term <= 0) && (this->i <= this->diffY); this->i++) {
			this->plotY += this->unitY;
			this->error_term += this->diffX;
		}
		this->error_term -= this->diffY;
		
		// Put the sample in the midpoint of the verticle line
		//*output = ((this->plotY + startY)/2);

		// Put the sample at the top of the verticle line
		*output = this->plotY;
		
		if (this->i > this->diffY)  
			return false;
		else
			return true;
	}
}


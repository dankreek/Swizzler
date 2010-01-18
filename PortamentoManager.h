#ifndef PORTAMENTOMANAGER_H
#define PORTAMENTOMANAGER_H

#include <inttypes.h>
#include "Bresenham.h"

class PortamentoManager {
  public:
	int16_t		curFreq;
	uint16_t	time;		// Time (in ms) for portamento
	bool		done;		// Is the current glide done?
	int16_t		destFreq;

	// Initialize portamento manager
	void		begin();

	// Put the portamento generator directly on a note
	void		nextDirectFreq(uint16_t freq);	

	// Put the portamento generator into a glide to the next note from the previous
	void 		nextGlideFreq(uint16_t freq);

	/**
	 * Process the next tick (ms in this case). 
	 * @return	true if the current frequency has changed, false if it does not
	 */
	bool		nextTick();

  private:
	int16_t		prevFreq;	

	Bresenham	timeLine;
};

#endif

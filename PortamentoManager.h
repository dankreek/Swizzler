#ifndef PORTAMENTOMANAGER_H
#define PORTAMENTOMANAGER_H

#include <inttypes.h>
#include "Bresenham.h"

class PortamentoManager {
  public:
	int16_t		prevFreq;	
	int16_t		destFreq;
	int16_t		curFreq;
	uint16_t	time;		// Time (in ms) for portamento
	bool		done;		// Is the current glide done?

	void		begin();
	void		nextDirectFreq(uint16_t freq);	
	void 		nextGlideFreq(uint16_t freq);

	/**
	 * Process the next tick (ms in this case). 
	 * @return	true if the current frequency has changed, false if it does not
	 */
	bool		nextTick();

  private:
	Bresenham	timeLine;
};

#endif

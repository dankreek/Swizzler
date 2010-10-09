/*
 * SineTable.cpp
 *
 *  Created on: Oct 2, 2010
 *      Author: justin
 */
#include "SineTable.h"

int16_t SineTable::getSine(uint16_t div) {
  if (div <= sineTableDivisions)
    return sineTable[div];
  else if (div <= (sineTableDivisions*2))
    return sineTable[(sineTableDivisions*2)-div];
  else if (div <= sineTableDivisions*3)
    return -sineTable[div-(sineTableDivisions*2)];
  else
    return -sineTable[(sineTableDivisions*4)-div];
}

// This is generated by scripts/SineTableGen.py
uint8_t SineTable::sineTable[] = {
  0,   13,  25,  37,  50,  62,  74,  86,
  98,  109, 120, 131, 142, 152, 162, 171,
  180, 189, 197, 205, 212, 219, 225, 231,
  236, 240, 244, 247, 250, 252, 254, 255,
  255
};
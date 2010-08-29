/*
 * DirectNoteFreqFilter.cpp
 *
 *  Created on: Aug 29, 2010
 *      Author: justin
 */

#include "DirectNoteFreqFilter.h"
#include "OscillatorMux.h"

DirectNoteFreqFilter::DirectNoteFreqFilter()
{
  // TODO Auto-generated constructor stub

}

void DirectNoteFreqFilter::noteOn(uint8_t noteNumber, uint8_t velocity) {
  sendFreq(OscillatorMux::noteToFreq(noteNumber));
}

void DirectNoteFreqFilter::noteOff(uint8_t noteNumber) {}

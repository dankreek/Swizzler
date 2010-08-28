#include <inttypes.h>
#include "OscillatorMux.h"
#include "PortamentoManager.h"
#include "MidiNoteBuffer.h"
#include "Swizzler.h"

bool OscillatorMux::portamentoOn;
uint8_t OscillatorMux::bendRange;
int8_t OscillatorMux::bendAmount;
OscillatorMux OscillatorMux::managers[Swizzler::numOscillators];

/**
 * Frequency -> Note lookup table. These are the frequencies for
 * the 8th octave. All the frequencies for the lower frequencies are
 * found by dividing.
 */
int note_lookup[] = {
	4186,	// C
	4435, 	// C#
	4699,	// D
	4978,	// D#
	5274,	// E
	5588,	// F
	5920,	// F#
	6272,	// G
	6645,	// G#
	7040,	// A
	7459,	// A#
	7902,	// B
};

OscillatorMux::OscillatorMux() {
  bendOffset = 0;
  portMan.init();
  noteOffset = 0;
}

void OscillatorMux::init() {
  portamentoOn = false;
  bendRange = 2;

  for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
    managers[i].oscNumber = i;
  }

  managers[1].setNoteOffset(5);
  managers[2].setNoteOffset(-12);
}

void OscillatorMux::newNote(uint8_t baseNoteNumber) {
  for (uint8_t i; i < Swizzler::numOscillators; i++) {
    managers[i].curMidiNote = (baseNoteNumber += managers[i].getNoteOffset());
    if (bendAmount != 0) {
      managers[i].recalculateBendOffset();
    }

    // If portamento's on, start the glide
    if (portamentoOn) {
      // If no previous note in the buffer then just play the note at its frequency
      if (MidiNoteBuffer::isEmpty()) {
        managers[i].portMan.nextDirectFreq(noteToFreq(managers[i].curMidiNote));
      }
      // If there is a previous note setup the glide
      else {
        managers[i].portMan.nextGlideFreq(noteToFreq(managers[i].curMidiNote));
      }
    }
    // If no portamento then set the frequency directly
    else {
      managers[i].setBaseFrequency(noteToFreq(managers[i].curMidiNote));
    }
  } // End For-Each oscillator
}

void OscillatorMux::enablePortamento(bool onOff) {
  // Turn portamento on
  if (onOff && !portamentoOn) {
    portamentoOn = true;
    for (uint8_t i=0; i < Swizzler::numOscillators; i++) managers[i].portMan.init();
  }
  // Turn portamento off
  else if (!onOff && portamentoOn) {
    portamentoOn = false;
    // If a destination frequency has been defined from a previous glide, jump directly to it
    for (uint8_t i=0; i < Swizzler::numOscillators; i++)
      if (managers[i].portMan.destFreq > -1) {
        managers[i].setBaseFrequency(managers[i].portMan.destFreq);
      }
  }
}

uint16_t OscillatorMux::noteToFreq(uint8_t noteNum) {
  /**
   * The MIDI standard defines note #0 as a 'C', so
   * divide the note number by 12 to get the octave the note is in
   * and take the remainder the find the note name.
   */
  int octave = noteNum / 12;
  int note = noteNum % 12;

  // Divides in half for the proper number of octaves
  // (every right shift is one less octave)
  return (note_lookup[note] >> (9-octave));
}

void OscillatorMux::setBendAmount(int8_t ba) {
  bendAmount = ba;
  for (int i=0; i < Swizzler::numOscillators;i++) {
    managers[i].recalculateBendOffset();
    managers[i].sendFrequency();
  }
}

void OscillatorMux::recalculateBendOffset() {
  // Bend up
  if (bendAmount > 0) {
    bendOffset = (bendAmount * (int16_t)(noteToFreq(curMidiNote+bendRange)-noteToFreq(curMidiNote)))/63;
  }
  // Bend down
  else if (bendAmount < 0) {
    //digitalWrite(8, true);
    bendOffset = (bendAmount * (int16_t)(noteToFreq(curMidiNote)-noteToFreq(curMidiNote-bendRange)))/64;
  }
  // No bend
  else {
    bendOffset = 0;
  }
}

void OscillatorMux::setBaseFrequency(uint16_t freq) {
  curFreq = freq;
  sendFrequency();
}

void OscillatorMux::sendFrequency() {
  Swizzler::soundChip.setFrequency(oscNumber, curFreq+bendOffset);
}

void OscillatorMux::nextTick() {
  // If portamento's on and running then output a new frequency
  for (uint8_t i; i < Swizzler::numOscillators; i++) {
    if (portamentoOn && !managers[i].portMan.done) {
      // only change frequency if it's necessary (save bandwidth on the wire)
      if (managers[i].portMan.nextTick()) managers[i].setBaseFrequency(managers[i].portMan.curFreq);
    }
  }
}

void OscillatorMux::setPortamentoTime(uint16_t time) {
  for (uint8_t i=0; i < Swizzler::numOscillators; i++) {
    managers[i].portMan.time = time;
  }
}

void OscillatorMux::setNoteOffset(int8_t offs) {
  noteOffset = offs;
  recalculateBendOffset();

}
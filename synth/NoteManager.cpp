#include "NoteManager.h"
#include "MidiNoteBuffer.h"
#include "Swizzler.h"

NoteManager::NoteManager() {
  init();
}

void NoteManager::init()  {
  MidiNoteBuffer::init();
}

void NoteManager::noteOn(uint8_t noteNumber, uint8_t velocity) {
  MidiNoteBuffer::putMidiNote(noteNumber);

  // Let the oscillator multiplexor know that a note has been started
  OscillatorMux::newNote(noteNumber);
  restartGate();
}

void NoteManager::restartGate() {
  for (int i=0;i<4;i++) Swizzler::soundChip.setEnvelopeGate(i, false);
  for (int i=0;i<4;i++) Swizzler::soundChip.setEnvelopeGate(i, true);
}

void NoteManager::noteOff(uint8_t noteNumber) {
  // Make sure the buffer's not already empty (could happen if a player mashes
  // down on a shitload of keys and lets them all off randomly)
  if (MidiNoteBuffer::size > 0) {
    // If this note is the current note that's playing then open the gate
    if (MidiNoteBuffer::getLastNote() == noteNumber) {
      for (int i=0;i<4;i++) Swizzler::soundChip.setEnvelopeGate(i, false);
    }

    MidiNoteBuffer::removeMidiNote(noteNumber);
  }
}

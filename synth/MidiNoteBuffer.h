#ifndef MIDINOTEBUFFER_H_
#define MIDINOTEBUFFER_H_

#include <inttypes.h>

/**
 * An ordered buffer that stores a list of midi notes to allow for areeggiating over them
 */
class MidiNoteBuffer {
public:
  static const uint8_t midiNoteBufSize = 24;

  // The current size of the list (how many keys are being held down)
  uint8_t size;

  // The index of the latest note that was struck in the buffer
  int8_t lastNote;

  // Initialize the Note Buffer
  MidiNoteBuffer();

  // Add a new midi note in-order
  void putMidiNote(uint8_t noteNumber);

  // Remove a midi note from the buffer
  void removeMidiNote(uint8_t noteNumber);

  // Macro to get the last note that was struck
  uint8_t getLastNote();

  // Buffer where the notes reside
  uint8_t buffer[midiNoteBufSize];

  // A little macro to check if the buffer is empty
  bool isEmpty();

private:
  // Create room for another element in the buffer at the given index
  void makeHole(uint8_t i);

  // Close the hole that a note left after being removed at the given index
  void closeHole(uint8_t i);
};

inline
uint8_t MidiNoteBuffer::getLastNote() {
 return buffer[lastNote];
}

inline
bool MidiNoteBuffer::isEmpty() {
  return (lastNote == -1);
}

#endif /*MIDINOTEBUFFER_H_*/

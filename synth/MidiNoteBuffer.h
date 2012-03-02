/** @file MidiNoteBuffer.h
 */
#ifndef MIDINOTEBUFFER_H_
#define MIDINOTEBUFFER_H_

#include <inttypes.h>

/**
 * An ordered list that stores midi notes to allow for arpeggiating over them in order.
 *
 * @author Justin May <may.justin@gmail.com>
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

  /**
   * Add a new MIDI note in-order
   *
   * @param noteNumber  MIDI note number to add
   */
  void putMidiNote(uint8_t noteNumber);

  /**
   * Remove a MIDI note from the buffer
   *
   * @param noteNumber  MIDI note number to remove
   */
  void removeMidiNote(uint8_t noteNumber);

  /** 
   * Get the last note that was entered into the list
   *
   * @return The MIDI note number that was last inserted
   */
  uint8_t getLastNote();

  /// Buffer where the notes reside
  uint8_t buffer[midiNoteBufSize];

  /**
   * Check if the buffer is empty
   *
   * @return True of the buffer is empty
   */   
  bool isEmpty();

private:
  /** 
   * Create room for another element in the buffer at the given index
   *
   * @param i   Index to insert an empty element at 
   */
  void makeHole(uint8_t i);

  /**
   * Close the hole that a note left after being removed at the given index
   *
   * @param i   Index in the list to remove an entry from
   */ 
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

#ifndef FREQMAN_H
#define FREQMAN_H

#include "Swizzler.h"
#include "PortamentoManager.h"

/**
 * The frequency manager takes in control messages (via MIDI) like note on, note off
 * portamento on/off, and arpeggio on/off and tells the oscillators what frequency to
 * put out at. This class contains 4 static members (one for each oscillator). that
 * are each modified by newNote() which is really the only public method that needs
 * to be called here. TODO: I should probably modify the header file to reflect this.
 */
class FrequencyManager {
public:
  FrequencyManager();

  // Which oscillator number is this (0-4, 4 is always noise)
  uint8_t oscNumber;

  PortamentoManager portMan;

  /**
   * Initialize the static components of the frequency manager
   */
  static void init();

  /**
   * The note manager is sending a new keyboard note which is then turned
   * into a frequency and sent to the proper voice on the sound chip
   */
  static void newNote(uint8_t noteNumber);

  /**
   * This is called once every millisecond to handle all the business.
   * Currently only the portamento manager needs a timer hook.
   */
  static void nextTick();

  /**
   * Set a new bend value 0 is max bend low, 64 is no bend, 127 is max high bend
   */
  static void setBendAmount(int8_t ba);

  /**
   * Turn on/off portamento
   * @onOff true to turn on portamento, false to turn off portamento
   */
  static void enablePortamento(bool onOff);

  /**
   * Convert a Midi note to a frequency
   */
  static uint16_t noteToFreq(uint8_t noteNum);

  // The range that the pitch bend swings between (in +/- half-steps)
  static uint8_t bendRange;

  // Set's the current base frequency (later modified with bends, LFO's, etc)
  void setBaseFrequency(uint16_t freq);

  // Set a new note offset for this oscillator (the offset by which the base is modified, in half-steps)
  void setNoteOffset(int8_t offset);
  uint8_t getNoteOffset();

  static void setPortamentoTime(uint16_t time);

  // A NoteManager for every voice (stored IN the note manager, it seems logical)
  static FrequencyManager managers[];

private:
  // Number of half-steps more or less then the basenote that should be played
  int8_t noteOffset;

  // Is portamento currently on?
  static bool portamentoOn;

  // Recalculate and send the current frequency modified by the pitch bender to the sound chip
  void sendFrequency();

  // Use the bendAmount and the current note number to recalculate the bendOffset
  void recalculateBendOffset();

  // How much to increment (or decrement) the output frequency (in hz) as set by recalculateBendOffset()
  int16_t bendOffset;

  // The last note that was sent
  uint8_t curMidiNote;

  // The current base frequency to be output
  uint16_t curFreq;

  // The current bend mount (-64-63)
  static int8_t bendAmount;


};

inline uint8_t FrequencyManager::getNoteOffset() {
  return noteOffset;
}

#endif

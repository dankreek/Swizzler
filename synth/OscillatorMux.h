#ifndef FREQMAN_H
#define FREQMAN_H

#include "Swizzler.h"
#include "PortamentoManager.h"

/**
 * The oscillator multiplexor takes in control messages (via MIDI) like note on, note off
 * portamento on/off and then sends that information into a frequency filter chain.
 * This class contains an array with 4 static members (one for each oscillator) that
 * are each modified by newNote() which is really the only public method that needs
 * to be called here.
 */
class OscillatorMux {
public:
  // ********* Static Level Methods ***********

  // Set the portamento time (in ms)
  static void setPortamentoTime(uint16_t time);

  // I'm storing an array of OscillatorMux's inside the OscillatorMux. It may seem a little
  // wierd, but it looks good on paper for right now...
  static OscillatorMux managers[];

  // Initialize the static components of the frequency manager
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

  // ********* Instance Level Methods ***********
  OscillatorMux();

  // Which oscillator number is this (0-4, 4 is always noise)
  uint8_t oscNumber;

  PortamentoManager portMan;

  // Set's the current base frequency (later modified with bends, LFO's, etc)
  void setBaseFrequency(uint16_t freq);

  // Set a new note offset for this oscillator (the offset by which the base is modified, in half-steps)
  void setNoteOffset(int8_t offset);
  uint8_t getNoteOffset();

private:
  // Is portamento currently on?
  static bool portamentoOn;

  // Number of half-steps more or less then the base note that should be played
  int8_t noteOffset;

  // The current bend mount (-64 - 63)
  static int8_t bendAmount;

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
};

inline uint8_t OscillatorMux::getNoteOffset() {
  return noteOffset;
}

#endif

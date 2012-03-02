/** @file MidiInput.h
 */
#ifndef MIDIINPUT_H_
#define MIDIINPUT_H_

#include "Swizzler.h"
#include "ANoteReceiver.h"
#include <inttypes.h>

/**
 * This is a utility class that handles MIDI input. Bytes are read in from some external source, 
 * (usually the UART) then pushed into the \a pushByte() method. When a complete MIDI command has
 * been sent, it will be acted upon.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class MidiInput {
public:  
  /// Event handler for a note on/off event
  static ANoteReceiver *noteReceiver;

  /// Pointer to an event handler for when a pitch bend event is recieved
  static void (*pitchBendEventHandler)();

  /// The current position of the pitch bend wheel (between -64 and 63)
  static int16_t pitchbendAmount;

  /// Max value of the pitch bend wheel
  static const int16_t bendMax = 63;

  /// Minimum value of the pitch bend wheel
  static const int16_t bendMin = -64;

  // MIDI command bytes for all the different types of MIDI commands. 
  // the lower nybble is the MIDI channel number
  static const unsigned char noteOff = 0x80;
  static const unsigned char noteOn = 0x90;
  static const unsigned char polyAfterTouch = 0xa0;
  static const unsigned char ctrlChange = 0xb0;
  static const unsigned char prgmChange = 0xc0;
  static const unsigned char afterTouch = 0xd0;
  static const unsigned char pitchbend = 0xe0;
  static const unsigned char sysExMsg = 0xf0;

  /**
   * Initialize all fields related to \a MidiInput
   */
  static void init();

  /**
   * Push a byte onto the MidiInput stack. Once an entire MIDI command is recieved, then
   * it will be processed.
   *
   * @param byte    The next byte in the MIDI input stream
   */
  inline static
  void pushByte(uint8_t byte) {
    // Throw out system real-time messages
    if ((byte > 0xf0) && (byte <= 0xff)) return;

    // This is a status byte, so start a new MIDI command
    if (byte & 0x80) {
      // If this command is not on our channel, then skip it
      // (hard coded to 1 for now, will make an option later)
      if ((byte & 0x0f) == 0) {
        midiCmd = byte;
        resetCommand();
      }
      else {
        // Set to no-message pending state
        init();
      }
    }
    else if ((midiCmd > -1) && (midiData1 == -1)) {
      midiData1 = byte;
    }
    else if ((midiCmd > -1) && (midiData2 == -1)) {
      midiData2 = byte;
    }

    // If a status byte is set, see if it's a complete command
    if (midiCmd >= 0x80)
      handleMidiCommand();
  }

  /**
   * If a status byte of some kind has been sent make sure there are enough data bytes for it.
   * If there are indeed enough data bytes, call the handler function
   */
  inline static
  void handleMidiCommand() {
    // Two byte commands
    if (midiData2 >= 0) {
      if (isCommandByte(noteOn))
        handleNoteOn();
      else if (isCommandByte(pitchbend))
        handlePitchBend();
      else if (isCommandByte(ctrlChange))
        handleControlChange();
      else if (isCommandByte(noteOff))
        handleNoteOff();

      // Ignoring aftertouch commands for now
      resetCommand();
    }
    // One byte commands
    else if (midiData1 >= 0) {
      if (isCommandByte(prgmChange)) {
        handleProgramChange();
        resetCommand();
      }
      // Ignore aftertouch
      else if (isCommandByte(afterTouch))
        resetCommand();
    }
    // No data commands
    else {
      // Ignore Sysex and real-time messages
      if (midiCmd >= 0xf0)
              resetCommand();
    }
  }


  /**
   * Determine if the last received MIDI command byte is of the type \p command 
   *
   * @param command     MIDI command to check for 
   * @return    True if \p midiCmd is of type \p command
   */
  inline static
  bool isCommandByte(int command) {
    return ((midiCmd & 0xf0) == command);
  }

  /**
   * Clear the current MIDI command
   */
  static inline
  void resetCommand() {
    midiData1 = -1;
    midiData2 = -1;
  }

  /// Handle Note Off event
  static void handleNoteOff();

  /// Handle Note On event
  static void handleNoteOn();

  /// Handle the pitch bend event
  static void handlePitchBend();

  /// Handle a MIDI controller change event
  static void handleControlChange();

  /// Handle the program change event
  static void handleProgramChange();

private:
  /// Current MIDI command byte
  static int midiCmd;

  /// First data byte in a MIDI message
  static int midiData1;

  /// Second data byte in a MIDI message
  static int midiData2;
};



#endif /*MIDIINPUT_H_*/

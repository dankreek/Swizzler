/** @file MidiControllerMapping.h
 *  @date Aug 7, 2010
 */

#ifndef MIDICONTROLLERMAPPING_H_
#define MIDICONTROLLERMAPPING_H_

#include <inttypes.h>

/**
 * This class contains a mapping for midi controller number and a method that should be called.
 *
 * @author Justin May <may.justin@gmail.com>
 */
class MidiControllerMapping {
public:
  /**
   * Create a mapping between a MIDI controller and a method
   *
   * @param ctrlNum     MIDI controller number
   * @param ctrlFunc    Method to be called when the MIDI controller message is recieved
   */
  MidiControllerMapping(uint8_t ctrlNum, void (*ctrlFunc)(uint8_t));

  /**
   * Loop through each MidiControllerMapping in the \p controllerList[] and execute
   * the controller's function if one is found.
   *
   * @param ctrlNum   Controller number to service
   * @param data      The data to pass into the controller function
   *
   * @return true if a handler was found, false if one wasn't.
   */
  static bool executeController(uint8_t ctrlNum, uint8_t data);

private:
  /// MIDI controller number to response to
  uint8_t controllerNumber;

  /**
   * Method to execute when receiving 
   *
   * @param value   MIDI controller value
   */
  void (*executeFunction)(uint8_t value);

  /**
   * This needs to be statically defined in the MidiControllerMapping source file
   * @see MidiControllerMapping.cpp for a deeper explanation of these
   */
  static MidiControllerMapping controllerList[];

  /**
   * Constant used to signify the end of the list is reached. (The highest midi controller number
   * is 0x7f, so 0xff will never occur in the MIDI stream.
   */
  static const uint8_t endOfMappingList = 0xff;
};

inline MidiControllerMapping::MidiControllerMapping(uint8_t ctrlNum, void (*func)(uint8_t)) {
  controllerNumber = ctrlNum;
  executeFunction = func;
}

inline bool MidiControllerMapping::executeController(uint8_t ctrlNum, uint8_t data) {
  for (uint8_t i=0; i < 0x80; i++) {
    if (controllerList[i].controllerNumber == ctrlNum) {
      controllerList[i].executeFunction(data);
      return true;
    }
    else if (controllerList[i].controllerNumber >= 0x80) {
      // Reached the end of the list, return false
      return false;
    }
  }

  return false;
}

#endif /* MIDICONTROLLERMAPPING_H_ */

/*
 * MidiControllerMapping.h
 *
 *  Created on: Aug 7, 2010
 *      Author: justin
 *
 *  This class contains a mapping for midi controller number and a function that should get executed
 */

#ifndef MIDICONTROLLERMAPPING_H_
#define MIDICONTROLLERMAPPING_H_

#include <inttypes.h>

class MidiControllerMapping {
public:
  // For each instance of MidiControllerMapping
  MidiControllerMapping(uint8_t ctrlNum, void (*ctrlFunc)(uint8_t));

  /**
   * Loop through each MidiControllerMapping in the array and execute
   * the controller's function if one is found.
   *
   * @ctrlNum   Controller number to service
   * @data      The data to pass into the controller function
   *
   * @return    true if a handler was found, false if one wasn't.
   */
  static bool executeController(uint8_t ctrlNum, uint8_t data);

private:
  // Each instance of a MidiControllerMapping has a number and a function to execute
  uint8_t controllerNumber;
  void (*executeFunction)(uint8_t);

  /**
   * This needs to be statically defined in the MidiControllerMapping source file
   * See MidiControllerMapping.cpp for a deeper explanation of these
   */
  static MidiControllerMapping controllerList[];
  static const uint8_t endOfMappingList = 0xff;
  //static uint8_t listLength;
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

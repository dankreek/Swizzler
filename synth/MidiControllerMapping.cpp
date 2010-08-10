/*
 * MidiControllerMapping.cpp
 *
 *  Created on: Aug 7, 2010
 *      Author: justin
 *
 * This file needs to be defined for every implementation of the Swizzler platform.
 *
 * This mostly-static class contains a list of instances of itself which contain
 * the mapping from a midi controller number to a function with the signature of
 * "bool func(uint8_t ctrlNum, uint8_t crtlVal)"
 *
 * Because this list is created at compile time the length of the mapping array
 * must be recorded here by hand.
 */
#include "MidiControllerMapping.h"

uint8_t MidiControllerMapping::listLength = 0;

MidiControllerMapping MidiControllerMapping::controllerList[] = {
//    MidiControllerMapping(1, (void*)(0))
};

/*
 * EnvelopeUtility.h
 *
 *  Created on: Sep 18, 2010
 *      Author: justin
 */

#ifndef ENVELOPEUTILITY_H_
#define ENVELOPEUTILITY_H_

class EnvelopeUtility {
public:
  // Close and open the gate for every voice
  static void restartGate();

  static void setGate(bool);
};

#endif /* ENVELOPEUTILITY_H_ */

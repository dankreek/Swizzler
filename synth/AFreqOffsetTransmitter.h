/** @file   AFreqTransmitter.h
 *  @date   Aug 28, 2010
 *  @author Justin May <may.justin@gmail.com>
 */

#ifndef AFREQTRANSMITTER_H_
#define AFREQTRANSMITTER_H_

#include <inttypes.h>
#include "AFreqOffsetReceiver.h"

/**
 * Class that contains abstract functionality for an effect that resides in the FrequencyFilterChain which
 * sends a frequency offset to the next effect in the chain.
 *
 * @see FreqFilterChain
 * @see AFreqOffsetReceiver
 */
class AFreqOffsetTransmitter {
public:
  /**
   * Links this frequency modulation effect to the next frequency modulation effect in the chain.
   *
   * @param receiver    Pointer to the next effect in the FreqFilterCHain
   */
  void linkTo(AFreqOffsetReceiver *receiver);

  /**
   * Sends this effect's current frequency offset to the next effect in the chain.
   *
   * @param schlipOffset    The frequency offset to send measured in schlips 
   */
  void sendSchlipOffset(int16_t schlipOffset);


  // TODO : I really don't think this is needed... think up a better strategy
  /**
   * Force a recalculation and send of the current frequency offset to the next effect in the chain.
   * This is generally called from the FreqFilterChain's nextTick() method for timer-based effects.
   */
  virtual void updateOffset() = 0;

private:
  /// The next effect in the frequency modulation effect chain
  AFreqOffsetReceiver *receiver;
};

inline
void AFreqOffsetTransmitter::linkTo(AFreqOffsetReceiver *output) {
  receiver = output;
}

inline
void AFreqOffsetTransmitter::sendSchlipOffset(int16_t offset) {
  receiver->recvOffset(offset);
}

#endif /* AFREQTRANSMITTER_H_ */

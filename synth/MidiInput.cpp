#include <inttypes.h>
#include "MidiInput.h"
#include "Swizzler.h"
#include "PresetManager.h"

int16_t MidiInput::midiCmd;
int16_t MidiInput::midiData1;
int16_t MidiInput::midiData2;

// Midi controller numbers
#define PORT_ON_OFF 67
#define PORT_TIME	10

#define ARP_ON_OFF	  26
#define ARP_TIME      12
#define ARP_MIN_NOTES 13

#define PITCH_BEND_RANGE  15

#define PULSE_WIDTH	 2

#define ATTACK_TIME     75
#define DECAY_TIME      76
#define SUSTAIN_LEVEL   92
#define RELEASE_TIME    95

#define SAVE_POWERON	84

#define OSC_1_WF        74
#define OSC_1_LEVEL     71

#define OSC_2_WF        91
#define OSC_2_LEVEL     93

#define OSC_3_WF        72
#define OSC_3_LEVEL     5



#define NOISE_LEVEL     7

void MidiInput::handleNoteOn() {
  /**
   * Most MIDI input devices send a NOTE ON message with a velocity of 0
   * to signal the note ending.
   */
  if (midiData2 == 0) NoteManager::noteOff(midiData1);
  else NoteManager::noteOn(midiData1);
}

void MidiInput::handleNoteOff() {	
  NoteManager::noteOff(midiData1);
}

void MidiInput::handlePitchBend() {
  // I'm going to ignore the least significant byte of this message for now
  // (my controller only sends 0 for the LSB anyway, so who cares)
  // This number comes in as an unsigned 7bit number, but internally I store it
  // as a signed 7 bit number. The -64 is to convert to signed.
  FrequencyManager::setBendAmount((int8_t)midiData2-64);
}

// Lots of fun with controllers!
void MidiInput::handleControlChange() {
  /**
   * In the MIDI protocol the 1st byte (midiData1) is the controller number and
   * the 2nd byte (midiData2) is the value of the controller (7bits)
   */
  switch (midiData1) {
  /**
   * Osc1 Controlls
   */
  case OSC_1_WF:
    SetParameters::setWaveform(0, midiData2);
    break;
  case OSC_1_LEVEL:
    SetParameters::setVoiceLevel(0, midiData2);
    break;

  case OSC_2_WF:
    SetParameters::setWaveform(1, midiData2);
    break;
  case OSC_2_LEVEL:
    SetParameters::setVoiceLevel(1, midiData2);
    break;

  case OSC_3_WF:
    SetParameters::setWaveform(2, midiData2);
    break;
  case OSC_3_LEVEL:
    SetParameters::setVoiceLevel(2, midiData2);
    break;

  case NOISE_LEVEL:
    Swizzler::soundChip.setWaveform(3,SoundDriver::noiseWave);
    SetParameters::setVoiceLevel(3, midiData2);
    break;

    /**
     * Portamento Controls
     */
    case PORT_ON_OFF:
            SetParameters::enablePortamento(midiData2);
            break;
    case PORT_TIME:
            SetParameters::setPortamentoTime(midiData2);
            break;

    case PULSE_WIDTH:
            SetParameters::setPulseWidth(midiData2);
            break;

    /**
     * Envelope value ares calculated using a knee
     */
    case ATTACK_TIME:
            SetParameters::setAttackTime(midiData2);
            break;
    case DECAY_TIME:
            SetParameters::setDecayTime(midiData2);
            break;
    case RELEASE_TIME:
            SetParameters::setReleaseTime(midiData2);
            break;
    case SUSTAIN_LEVEL:
            SetParameters::setSustainLevel(midiData2);
            break;

    // Arpeggio controls
    case ARP_ON_OFF:
            SetParameters::enableArpeggio(midiData2);
            break;
    // Arp time is measured in milliseconds per note
    case ARP_TIME:
            SetParameters::setArpeggioTime(midiData2);
            break;
    case ARP_MIN_NOTES:
            SetParameters::setArpeggioMinNotes(midiData2);
            break;

    case PITCH_BEND_RANGE:
            SetParameters::setBendRange(midiData2);
            break;

    case SAVE_POWERON:
            PresetManager::storePreset();
  }
}

void MidiInput::handleProgramChange() {
	PresetManager::loadPreset(midiData1);
}

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <inttypes.h>

enum InputState {
	PRINTING,         // Currently priuntg characters
	READING_COMMAND,  // The command char (0xfe) was sent, now awaiting command type
	READING_COMMAND_DATA  // Reading data for command
};

enum CommandByte {
	NONE = 0x00,
	AUTO_SCROLL_ON = 0x51,
	AUTO_SCROLL_OFF = 0x52,
	CLEAR_SCREEN = 0x58,
	AUTO_WRAP_ON = 0x43,
	AUTO_WRAP_OFF = 0x44,
	SET_CURSOR_POS = 0x47,
	GO_HOME = 0x48,
	MOVE_CURSOR_BACK = 0x4c,
	MOVE_CURSOR_FWD = 0x4d,
	UNDERLINE_ON = 0x4a,
	UNDERLINE_OFF = 0x4b,
	BLINK_ON = 0x53,
	BLINK_OFF = 0x54
};

#define COMMAND_CHAR 0xfe

/**
 * This class will later contain methods to change which port is being read from (twi, 
 * serial, or SPI)
 */
class InputHandler {
    public:
	/**
	 * Initialize the input handler
	 */
	static void init();

	/**
	 * Recieve one character into input handler
	 */
	static void recvByte(uint8_t got);
    private:
	/**
	 * The current state of the input stream
	 */
	static InputState curState;

	/**
	 * Current command being input
	 */
	static CommandByte curCmd;

	/**
	 * Where command data is stored
	 */
	static uint8_t cmdData[];

	/**
	 * Number of bytes stored in cmdData
	 */
	static uint8_t cmdDataSize;
};

#endif

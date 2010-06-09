#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

//	LCD Port Information (from microcontroller)
#define	LCD_OUT		PORTD
#define	LCD_IN		PIND
#define	LCD_DDR		DDRD
#define	ENABLE		6
#define	RW		5
#define	RS		4
#define	D7		3
#define	D6		2
#define	D5		1
#define	D4		0

//	Register Select Constants
#define	DATA_REGISTER		0
#define	COMMAND_REGISTER	1

#define DISPLAY_ONOFF_ADDY	0x08

// Original author used an interrupt as a timer, this is much simpler
#define delay50us(x) for (int i=0; i<x; i++) _delay_us(50)

class LcdDisplay {
    public:
	/**
	 * If true then the screen scrolls and creates a new line when printing beyond the last line,
	 * otherwise just go back to the upper-left corner 
	 */
	static volatile bool autoScroll;

	/**
	 * Initialize the display
	 */
	static void init(uint8_t width, uint8_t height);	

	/**
	 * Write a string, character or byte to the display
	 */
	static void write(char* str); 
	static void write(char c);
	static void inline write(uint8_t b) {
		write((char)b);
	}

	/**
	 * Put cursor at location X, Y
	 */
	static void moveCursor(uint8_t x, uint8_t y);

	/**
	 * Clear the screen
	 */
	static void clear();


	/**
	 * Scroll the text on the display up one row
	 */
	static void scrollDown();

	/**
	 * Send the cursor to the home position
	 */
	static inline void goHome() {
		moveCursor(0,0);
	}

	/**
	 * Set the display on/off and cursor properties
	 */
	static void setDisplayProperties(bool displayOn, bool underlineOn, bool blockBlinkOn);


	static void setUnderline(bool);
	static void setBlink(bool);
    private:
	static bool underlineOn;
	static bool blinkOn;

	// Cursor's current position
	static volatile uint8_t position;

	/**
	 * Since the character positions are wierd, we keep the first char in 
	 * each row's address to compute X,Y coordinate addresses
	 */
	static uint8_t rowAddress[4];

	/**
	 * Perform the action that  newline chracter would (go to beginning of next line)
	 */
	static void newLine();

	/**
	 * Handle a backspace character
	 */
	static void bs();

	/**
	 * Handle end-line character
	 */
	static void endLine();

	/**
	 * Perform a carriage return
	 */
	static void cr();

	/**
	 * Writes a byte to the display
	 */
	static void writeByte(uint8_t reg, uint8_t byte);

	/**
	 * Polls the ready bit on the LCD to ensure that the
	 * LCD is able to receive a new command or new data, or
	 * delays for about 50 microseconds.
	 */
	static void waitForReady();

	/**
	 * Writes a nibble to the display
	 */
	static void writeNibble(uint8_t reg, uint8_t nibble);

	/**
	 * Read a nibble from the display
         */
	static uint8_t readNibble(uint8_t reg);
	
	/**
	 * Read a byte from the display
	 */
	static uint8_t readByte(uint8_t reg);
	


	// Width and height of the display
	static uint8_t width;
	static uint8_t height;
};

#endif

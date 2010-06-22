#include "LcdDisplay.h"

// Each row starts on a randomly chosen address, no idea why
#define FIRST_ROW_ADDRESS   0x00
#define SECOND_ROW_ADDRESS  0x40
#define THIRD_ROW_ADDRESS   0x14
#define FOURTH_ROW_ADDRESS  0x54

volatile bool LcdDisplay::autoScroll;
volatile uint8_t LcdDisplay::position;
uint8_t LcdDisplay::rowAddress[] = {FIRST_ROW_ADDRESS, SECOND_ROW_ADDRESS, THIRD_ROW_ADDRESS, FOURTH_ROW_ADDRESS};
uint8_t LcdDisplay::width, LcdDisplay::height;
bool LcdDisplay::underlineOn, LcdDisplay::blinkOn;

void LcdDisplay::init(uint8_t w, uint8_t h) {
	width = w;
	height = h;		

	autoScroll = true;
	
	// Set the position counter to 0
	position = 0;
	
	// Set the proper data direction for output
	LCD_CTRL_DDR |= 0x70;
	LCD_DATA_DDR |= 0x0f;

	// First, delay50us for at least 15ms after power on
	delay50us(300);
	
	// Set for 4-bit LCD mode
	writeNibble(COMMAND_REGISTER, 0x03);
	delay50us(100);
	writeNibble(COMMAND_REGISTER, 0x03);
	delay50us(100);
	writeNibble(COMMAND_REGISTER, 0x03);
	delay50us(100);
	writeNibble(COMMAND_REGISTER, 0x02);
	delay50us(100);
	
	// Function set
	writeByte(COMMAND_REGISTER, 0x28);
	delay50us(250);
	
	// Turn display off
	setDisplayProperties(false, false, false);	

	// Clear LCD and return home
	clear();
	
	// Turn on display
	setDisplayProperties(true, false, false);
}

void LcdDisplay::waitForReady(void) {
	//	Poll the busy flag until it goes clear -- which means
	//	that new instructions may be given to the LCD screen
	//while((readByteFromLCD(COMMAND_REGISTER) & 0x80) == 0x80);
	
	//	Or.... delay 50us
	_delay_us(50);
}

void LcdDisplay::writeNibble(uint8_t reg, uint8_t nibble) {
	// Clear out the control bits
	LCD_CTRL &= 0x8f;

	//	Pull the enable line high
	LCD_CTRL |= _BV(ENABLE);

	// Clear the data bits
	LCD_DATA &= 0xf0;

	//	Output the nibble to the LCD
	LCD_DATA |= nibble;
	
	//	Determine if the register select bit needs to be set
	if (reg == DATA_REGISTER) LCD_CTRL |= _BV(RS);
	else LCD_CTRL &= ~_BV(RS);
	
	//	Toggle the enable line to latch the nibble
	LCD_CTRL &= ~_BV(ENABLE);
}

void LcdDisplay::write(char c) {
	// If this is a special control character, do its duty
	if (c == 0x08) bs();
	else if (c == 0x0c) clear();
	else if (c == 0x0d) cr();
	else if (c == 0x0a) newLine();
	else {
		// Write the character out to the display
		writeByte(DATA_REGISTER, c);

		// Incrememnt the position
		position++;

		// Change the cursor position if at the end of a line
		if (position == (width*height)) {
			if (autoScroll) scrollDown(); 
			else goHome();
		}
		// Wrap to next line 
		else if ((position % width) == 0) {
			moveCursor(0, position/width);
			delay50us(25);
		}
	}
}

void LcdDisplay::writeByte(uint8_t reg, uint8_t byte) {
	// Generate the high and low part of the bytes that will be
	// written to the LCD
	uint8_t upperNibble = byte >> 4;
	uint8_t lowerNibble = byte & 0x0f;
	
	// Wait for the LCD to become ready
	waitForReady();
	
	// First, write the upper four bits to the LCD
	writeNibble(reg, upperNibble);
	
	// Finally, write the lower four bits to the LCD
	writeNibble(reg, lowerNibble);
}

uint8_t LcdDisplay::readNibble(uint8_t reg) {
	uint8_t nibble = 0x00;
	
	// Set the data direction for the incoming data
	LCD_DATA_DDR &= 0xf0;
	
	// Turn on the enable, set the read/write pin to read
	// and clear the rest of the port
	LCD_CTRL |= _BV(ENABLE) | _BV(RW);
	
	// Determine if the register select bit needs to be set
	if(reg == DATA_REGISTER) {
		// If so, then set it
		LCD_CTRL |= _BV(RS);
	}
	else {
		// Otherwise, clear the register select bit
		LCD_CTRL &= ~_BV(RS);
	}
	
	// Wait some number of clock cycles for the data to become
	// steady on the 4-bit data bus
	_delay_us(38); 

	// Read the data bus and mask only the lower four bits of the port
	nibble = LCD_DATA_IN & 0x0f;
	
	// Clear the enable
	LCD_CTRL &= ~_BV(ENABLE);
	
	// Clear the read/write strobe
	LCD_CTRL &= ~_BV(RW);
	
	// Return the data direction to the original state
	LCD_DATA_DDR |= 0x0f;

	LCD_CTRL_DDR |= 0x70;
	
	// Finally, return the nibble
	return nibble;
}

uint8_t LcdDisplay::readByte(uint8_t reg) {
	// Create variables for the lower and upper nibbles as well as the
	// entire byte (a combination of the upper/lower nibbles, of course)
	uint8_t byte = 0x00;
	uint8_t upperNibble = 0x00;
	uint8_t lowerNibble = 0x00;
	
	// Read the upper nibble
	upperNibble = readNibble(reg);

	// Read the lower nibble
	lowerNibble = readNibble(reg);
	
	// Combine the upper and lower nibbles to produce the full 8-bit byte
	byte = (upperNibble << 4) | lowerNibble;
	
	// Finally, return the byte
	return byte;
		
}

void LcdDisplay::write(char* str)  { 
	while (*str) write(*str++);
}

void LcdDisplay::clear() {
	// Send command to LCD (0x01)
	writeByte(COMMAND_REGISTER, 0x01);
	
	// Set the current position to 0
	position = 0;	

	_delay_ms(11);
}

void LcdDisplay::moveCursor(uint8_t x, uint8_t y) {
	position = (y*width) + x;
	writeByte(COMMAND_REGISTER, 0x80|(x + rowAddress[y]));
}

void LcdDisplay::scrollDown() {
	// Move the top lines up
	for (int row=0; row < (height-1); row++) {
		// Copy the next row to this row
		for (int col=0; col < width; col++) {
			moveCursor(col, row+1);
			uint8_t oldChar = readByte(DATA_REGISTER);
			moveCursor(col, row);
			writeByte(DATA_REGISTER, oldChar);
		}		
	}

	// Create a blank line
	moveCursor(0, height-1);
	for (int i=0; i <width; i++)
		writeByte(DATA_REGISTER,' ');

	// Move cursor to start of line
	moveCursor(0, height-1);
}

void LcdDisplay::newLine() {
	// If the cursor is on one the top lines, go to the next line
	if (position < (width*(height-1))) {
		moveCursor(0, (position/width)+1);
	}
	// If on the bottom line then just scroll down what's already on the display
	else {
		scrollDown();
	}
		
}

void LcdDisplay::cr() {
	// Put the cursor at the beginning of the current line
	moveCursor(0, position/width);
}

void LcdDisplay::bs() {
	if (position == 0) return;

	// Move the cursor back one, delete the character, then put the cursor back again
	uint8_t newPos = (position-1);
	moveCursor(newPos%width, newPos/width);
	writeByte(DATA_REGISTER, ' ');
	moveCursor(newPos%width, newPos/width);
}

void LcdDisplay::setDisplayProperties(bool displayOnOff, bool underlineOnOff, bool blockBlinkOnOff) {
	uint8_t displaySettings=DISPLAY_ONOFF_ADDY;

	underlineOn = underlineOnOff;
	blinkOn = blockBlinkOnOff;
	
	if (displayOnOff) displaySettings |= 0x04;
	if (underlineOnOff) displaySettings |= 0x02;
	if (blockBlinkOnOff) displaySettings |= 0x01;

	writeByte(COMMAND_REGISTER, displaySettings);
	delay50us(250);	
}

void LcdDisplay::setUnderline(bool onOff) {
	underlineOn = onOff;
	setDisplayProperties(true, underlineOn, blinkOn);
}

void LcdDisplay::setBlink(bool onOff) {
	blinkOn = onOff;
	setDisplayProperties(true, underlineOn, blinkOn);
}


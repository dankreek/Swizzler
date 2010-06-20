#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "TwoWireSlave.h"
#include "LcdDisplay.h"
#include "InputHandler.h"
#include "TimerHandler.h"

#define TRUE 1
#define FALSE 0

#include "RingBuffer.cpp"

#ifdef __cplusplus 
extern "C"{ 
 FILE * uart_str; 
} 
#endif 

#define TWI_INPUT_BUFER_SIZE	32
uint8_t inputSpace[TWI_INPUT_BUFER_SIZE];
RingBuffer<uint8_t> inputBuffer(inputSpace, TWI_INPUT_BUFER_SIZE);

static int lcd_putchar(char,FILE*);
void recvTwiData(int);
#undef FDEV_SETUP_STREAM 
#define FDEV_SETUP_STREAM(p, g, f) { 0, 0, f, 0, 0, p, g, 0 }
FILE lcd_out = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

/*
**	Function to output a character to the LCD if using printf.  Uncomment
**	if needed
*/
static int lcd_putchar(char ch, FILE *unused) {
	LcdDisplay::write(ch);
	return 0;
}

/*
**	Main Function
*/
int main(void) {	
	stdout = &lcd_out;

	// Initialize the LCD
	LcdDisplay::init(16, 2);

	// Initialize TWI bus
	twi.init(0x69, &inputBuffer);

	// Initialize the timer interrupt
	TimerHandler::init();



	// Initialize the input handler
	InputHandler::init();

	// Enable interrupts
	sei();

	while(TRUE) {
		if (inputBuffer.hasData()) {
			InputHandler::recvByte(inputBuffer.popFront());
		}

		// Won't run without this, I probably really need some synchronization code
		_delay_us(5);

	}
	return 0;
}

/*
void recvTwiData(int count) {
	while (twi.available()) {
		//char c = Wire.receive();
		// printf("\n%3d = '%c'", (unsigned char)c, c);
		//InputHandler::recvByte(Wire.receive());
		inputBuffer.pushBack(twi.receive());
	}
}
*/

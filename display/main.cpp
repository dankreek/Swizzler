#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "Wire.h"
#include "LcdDisplay.h"
#include "InputHandler.h"

#define TRUE 1
#define FALSE 0

#ifdef __cplusplus 
extern "C"{ 
 FILE * uart_str; 
} 
#endif 

static int lcd_putchar(char,FILE*);
void gotData(int);
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
	Wire.begin(0x69);
	Wire.onReceive(gotData);

	// Initialize the input handler
	InputHandler::init();

	// Enable interrupts
	sei();

	while(TRUE) {
		// Sit on thumb
		_delay_ms(100);	
	}
	return 0;
}

void gotData(int count) {
	while (Wire.available()) {
		//char c = Wire.receive();
		// printf("\n%3d = '%c'", (unsigned char)c, c);
		InputHandler::recvByte(Wire.receive());
	}
}


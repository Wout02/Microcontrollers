/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** lookup.c
**
** Beschrijving:	Ledpatroon op PORTD dmv table lookup (scheiding logica en data)    
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c switch.c
**					avr-gcc -g -mmcu=atmega128 -o lookup.elf lookup.o
**					avr-objcopy -O ihex lookup.elf lookup.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int counter = 0;

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

PATTERN_STRUCT pattern[] = { 
	{0x80, 150}, {0x00, 150}, 
	{0x80, 150}, {0x00, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x00, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},	
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x00, 150},
	{0xFF, 0}
};

/******************************************************************
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char	Numbers [16] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001  // F
	};

void display (int digit){
	if (digit > 16)
	{
		PORTB = Numbers[14];
	}else{
		PORTB = Numbers[digit];
	}
}

void reset(){
	counter = 0;
}

void add(){
	counter++;
}

void subtract(){
	if (counter == 0)
	{
		reset();
	}else{
		counter--;
	}
}



/******************************************************************
short:			main() loop, entry point of executable
inputs:
outputs:
notes:
Version :    	DMK, Initial code
*******************************************************************/
int main( void ) {
	DDRB = 0b11111111;					// PORTB all output 
	DDRC = 0x00;
	DDRD = 0x00;
	while (1) {
		
		if (PINC)
		{
			add();
			wait(200);
		}
		if (PIND)
		{
			subtract();
			wait(200);
		}
		if (PIND && PINC)
		{
			reset();
			wait(200);
		}
		
		display(counter);
		
		
		
	
		/*
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD	
			PORTB = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
		*/
	}

	return 1;
}

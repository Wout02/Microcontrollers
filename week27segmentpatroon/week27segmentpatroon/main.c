#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0b00000001, 100},{0b00000010, 100},{0b00000100, 100},{0b00001000, 100},{0b00010000, 100},{0b00100000, 100},
	{0b00000001, 50},{0b00000010, 50},{0b01000000, 50},{0b00010000, 50},{0b00001000, 50},{0b00000100, 50},{0b01000000, 50},{0b00100000, 50},
	{0b00000001, 50},{0b00000010, 50},{0b01000000, 50},{0b00010000, 50},{0b00001000, 50},{0b00000100, 50},{0b01000000, 50},{0b00100000, 50},	
	{0b00000001, 100},{0b00000010, 100},{0b00000100, 100},{0b00001000, 100},{0b00010000, 100},{0b00100000, 100},	
	{0x00,0x00}
	
};

/******************************************************************/
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


/******************************************************************/
int main( void )
{
	DDRB = 0b11111111;					// PORTD all output 
	
	while (1==1)
	{
		int index = 0;
		while( pattern[index].delay != 0 ) {	
			PORTB = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}

	return 1;
}

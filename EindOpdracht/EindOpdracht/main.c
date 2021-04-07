#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

// Function to wait a number of microseconds
void wait( int us )
{
	for (int i=0; i<us; i++)
	{
		_delay_us( 1 );			
	}
}

// initializes the ADC
void adcInit( void ) {
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}


int main( void )
{
	DDRA = 0xFD; //Button A.1 for input
	DDRB = 0xFD; //Button B.1 for input
	DDRD = 0xFD; //Button D.1 for input
	DDRC = 0xFF; //PORT C for output for buzzer
	DDRF = 0x00; //PORT F for input for ADC
	adcInit();   //initializes the ADC
	
	int TONE = 1; //default tone

	while (1)
	{
		if (PINA)
		{
			TONE = 1; // highest tone
		}
		if (PINB)
		{
			TONE = 2; // middle tone
		}
		if (PIND)
		{
			TONE = 3; // lowest tone
		}
		PORTC ^= BIT(1); // Toggles the bit on C1 to trigger the buzzer
		wait(ADCH*TONE); // The tone is determined by the potentiometer and the pressed button. 		
	}
}


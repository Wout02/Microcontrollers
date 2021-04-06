/*
 * GccApplication1.c
 *
 * Created: 3-2-2021 09:33:46
 * Author : bart
 */ 



#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms){
	for (int i = 0;i<ms;i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	//DDRC = 0x00;
    while (1) 
    {
		//if (PINC && 0x80)
		//{
			////PORTD = 0x80;
			////wait(500);
			//PORTD = 0x00;
			//wait(500);
		//}else{
			//PORTD = 0x00;
		//}
		for (int i = 0; i<8;i++)
		{
			PORTD = 0x01 << i;
			wait(500);
		}
		

    }
}


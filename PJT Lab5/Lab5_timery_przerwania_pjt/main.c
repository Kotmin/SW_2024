/*
 * Lab5_timery_przerwania_pjt.c
 *
 * Created: 18.11.2022 16:16:38
 * Author : Student_PL
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define F_CPU 1000000L
/*

volatile int licznik = 0;


void time10()
{
	
	while(!(TIFR & (1<<OCF0))){}
		TIFR |= (1<<OCF0);
		
}

void time1sec(){
	for(int i=0;i<100;i++)
		time10();
}


ISR(TIMER0_COMP_vect) {
	
	licznik++;
	
}
*/
int main(void)
{
	DDRA = 0xff;
	DDRB=0xFF;
	PORTA = 0x00;
	PORTB = 0x01;
	//OCR0 = 38;
	
	
	TIMSK|= 1<<TOIE0;
	
	
    /* Replace with your application code */
	
	//TCCR0 |= (1 << CS02) | (1<<WGM01); // ctc z pre256 ,dla normal ignore
	
	
	//TIMSK |= (1<<OCIE0); dla przerwan
	int display= 0;
	TCCR0 |= (1<<CS00) | (1<<CS01) | (1<<CS02);
	//sei();
	
	TCNT0= 240;
	
    while (1) 
    {	
		//time10();
		//time1sec();
		/*
		if (licznik>=100)
		{
			licznik = 0;
			PORTA ^= (1 << PA0);
		}
		*/
		
		display = TCNT0;
		PORTA = display;
		
		//sprawdzenie stanu flagi przepe³nienia
		if(TIFR & (1 << TOV0))
		{ //jeœli flaga przepe³nienia ustawiona, to:
			TCCR0 &= ~((1<<CS00) | (1<<CS01) | (1<<CS02));
		}
		_delay_ms(200);
	}
}


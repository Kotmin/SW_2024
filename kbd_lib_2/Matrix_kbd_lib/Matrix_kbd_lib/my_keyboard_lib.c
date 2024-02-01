#include "my_keyboard_lib.h"


static volatile uint8_t key_code;


const uint8_t kolumny [] PROGMEM = {16,32,64,128};

const uint8_t tab [] PROGMEM = {
								1,2,3,4,
								5,6,7,8,
								9,10,11,12,
								13,14,15,16,
								0};

void set_DDR(char port_name){
	switch(port_name){
		case 'A':
		DDRA = 0xF0;
		PORTA=0x0F;
		
		break;
		case 'B':
		DDRB = 0xF0;
		PORTB=0x0F;
		
		break;
		case 'C':
		DDRC = 0xF0;
		PORTC=0x0F;
		
		break;
		
		case 'D':
		DDRD = 0xF0;
		PORTD=0x0F;
		
		break;

	}
	

}



int8_t get_key(const char type, const char port_name) 
{
	int8_t temp, row = 0,ret_key_index_number = 0, state,h_port,l_port;
	if(type == 'M' | type =='m'){
		state = ~(1<<4); //wstawiamy to zero krocz�ce, w zasadzie to w tym przypadku nie kroczace
		setPort(port_name, state);
		_delay_ms(10);
		temp = getPin(port_name);

			return translate(temp);
		
	}
	
	if(type == 'D' | type =='d')
	{
		/*
		setPort(port_name, state);
		_delay_ms(20);
		
		l_port = getPin(port_name) & 0x0F;
		h_port = getPin(port_name) &0xF0;
		Tutaj w zasadzie idac za tym pomyslem az sie prosi to skumulowac do 4 bitow w ukladzie 0x_ _ _ _ W W K K i miec 4 bity wolne, ale to tylko dywagacja
					*/
			for(int col=4; col<8; col++) // column
			{
				state = ~(1<<col);
				setPort(port_name, state);
				_delay_ms(10);
				temp = getPin(port_name);
				row = translate(temp);
				if(row != 0)
					ret_key_index_number = (row-1)*4 + col - 3;
	
				
			}//koniec fora

			}//koniec if d
			return ret_key_index_number;
		
		
		
	
}//koniec getKey


void setPort(const char port_name, int8_t state)
{
	switch(port_name)
	{
		case 'A':
		PORTA = state;
		break;
		case 'B':
		PORTB = state;
		break;
		case 'C':
		PORTC = state;
		break;
		case 'D':
		PORTD = state;
		break;
	}
	
}
int8_t getPin(const char port_name)
{
	int8_t x=0xbF0;
	switch(port_name)
	{
		case 'A':
		x = 0x0F & PINA;
		break;
		case 'B':
		x = 0x0F & PINB;
		break;
		case 'C':
		x = 0x0F & PINC;
		break;
		case 'D':
		x = 0x0F & PIND;
		break;
	}
	return x;
}



int8_t translate(int key_rcode){
		switch(key_rcode)
		{
		case 0b00001110:
			return  1;
		break;
		case 0b00001101:
			return 2;
			break;
		case 0b00001011:
			return 3;
			break;
		case 0b00000111:
			return 4;
			break;
		default:
			return 0;
				}
}

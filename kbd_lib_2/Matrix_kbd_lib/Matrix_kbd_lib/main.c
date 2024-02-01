
#include <avr/io.h>



#include "my_keyboard_lib.h"

int main(void)
{
	
	set_DDR('A');
	//Ledy
	DDRB =0xFF;
	PORTB =0xFF;
	
    while (1) 
    {
		PORTB = get_key('d', 'A');
    }
}


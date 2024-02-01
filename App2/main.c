#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd_lib.h"
#include "my_keyboard_lib.h"
#include "menu.h"

#define F_CPU 1000000UL


LCD lcd1;




int main(void) {
	// Set kbd
	set_DDR('A');
	//Led bar
	DDRD =0xFF;
	PORTD =0xFF;
	
	
    LCD_init(&lcd1, 'B');

	Menu menu;
    menu_init(&menu, &lcd1);


	menu_display(&menu);

	
	timer0_init();
	timer2_init();
	sei();
	char lastKey;

    while (1) 
    {
		 char key = get_key('d', 'A');
		 
		 //  refresh screen if changed
		 if(lastKey!=key) {
         	menu_display(&menu);

		 switch (key) {
            case 4: // Up
                menu_prevItem(&menu);
                break;
            case 8: // Down
                menu_nextItem(&menu);
                break;
            case 12:  // Enter
			menu_actionForward(&menu);
                
                break;
            case 16: // Return
                
				menu_actionBackward(&menu);
                break;
       			 }
		}
		lastKey = key;
		
		
	}
}


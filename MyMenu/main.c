#include <avr/io.h>
#include <stdio.h>

#include "lcd_lib.h"
#include "my_keyboard_lib.h"
#include "menu.h"

#define F_CPU 1000000UL

int main(void) {
	// Set kbd
	set_DDR('A');
	//Led bar
	DDRD =0xFF;
	PORTD =0xFF;
	
	LCD lcd1;
    LCD_init(&lcd1, 'B'); // Initialize LCD on PORTB

	Menu menu;
    menu_init(&menu, &lcd1);


	menu_display(&menu);

	
	char lastKey;

    while (1) 
    {
		 char key = get_key('d', 'A');
		 
		 // only refresh screen if key state is changed
		 if(lastKey!=key) {
         	menu_display(&menu);

		 switch (key) {
            case 4: // Up
                menu_prevItem(&menu);
                break;
            case 8: // Down
                menu_nextItem(&menu);
                break;
            case 12:  // Return
                menu_actionBackward(&menu);
                break;
            case 16: // Enter
                
				menu_actionForward(&menu);
                break;
       			 }
		}
		lastKey = key;
		
		
	}
}


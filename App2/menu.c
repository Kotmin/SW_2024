#include "menu.h"
#include "lcd_lib.h"
#include <string.h>

#include <avr/interrupt.h>



void menu_init(Menu *menu, LCD *lcd) {
    static MenuItem option1, option2, option3;
    static MenuItem option1_1, option1_2;
    static MenuItem option2_1, option2_2;
	static MenuItem option3_1, option3_2;

    menu->current = &option1;
    menu->lcd = lcd;
    // ================== option 1 ==================
    strcpy(option1.text,"Menu 1");
    option1.next = &option2;
    option1.prev = NULL;
    option1.child = NULL;
    option1.parent = NULL;
    option1.actionForward = &moveToChild;
    option1.actionBackward = &moveToParent;

    // ================== option 2 ==================
    strcpy(option2.text,"Menu 2");
    option2.next = &option3;
    option2.prev = &option1;
    option2.child = NULL;
    option2.parent = NULL;
    option2.actionForward = &moveToChild;
    option2.actionBackward = &moveToParent;

    // ================== option 3 ==================
    strcpy(option3.text,"Menu 3");
    option3.next = NULL;
    option3.prev = &option2;
    option3.child = NULL;
    option3.parent = NULL;
    option3.actionForward = &moveToChild;
    option3.actionBackward = &moveToParent;

    // ================== option 1_1 ==================
    strcpy(option1_1.text,"Program 1_1");
    option1_1.next = &option1_2;
    option1_1.prev = NULL;
    option1_1.child = NULL;
    option1_1.parent = &option1;
    option1.child = &option1_1; // link parent
    option1_1.actionForward = foo1; ///////////////////////
    option1_1.actionBackward = &moveToParent;

    // ================== option 1_2 ==================
    strcpy(option1_2.text,"Program 1_2");
    option1_2.next = NULL;
    option1_2.prev = &option1_1;
    option1_2.child = NULL;
    option1_2.parent = &option1;
    option1_2.actionForward = foo1;
    option1_2.actionBackward = &moveToParent;

    // ================== option 2_1 ==================
    strcpy(option2_1.text,"Program 2_1");
    option2_1.next = &option2_2;
    option2_1.prev = NULL;
    option2_1.child = NULL;
    option2_1.parent = &option2;
    option2.child = &option2_1; // link parent
    option2_1.actionForward = foo2_1;
    option2_1.actionBackward = &moveToParent;

    // ================== option 2_2 ==================
    strcpy(option2_2.text,"Program 2_2");
    option2_2.next = NULL;
    option2_2.prev = &option2_1;
    option2_2.child = NULL;
    option2_2.parent = &option2;
    option2_2.actionForward = foo2_2;
    option2_2.actionBackward = &moveToParent;

	    // ================== option 3_1 ==================
    strcpy(option3_1.text,"Program 3_1");
    option3_1.next = &option3_2;
    option3_1.prev = NULL;
    option3_1.child = NULL;
    option3_1.parent = &option3;
    option3.child = &option3_1; // link parent
    option3_1.actionForward = foo3;
    option3_1.actionBackward = &moveToParent;

		    // ================== option 3_2 ==================
    strcpy(option3_2.text,"Powrot do Menu1");
    option3_2.next = NULL;
    option3_2.prev = &option3_1;
    option3_2.child = &option1_1;
    option3_2.parent = &option3;

    option3_2.actionForward = &moveToChild;
    option3_2.actionBackward = &moveToParent;
}


void menu_display(Menu *menu) {
	if(menu == NULL || menu->current == NULL)
		return;
	
    LCD_clear(menu->lcd);

    LCD_writeCharacter(menu->lcd, '>');
	if(menu->current->child != NULL)
		LCD_writeCharacter(menu->lcd, '+');
	
	LCD_writeText(menu->lcd, menu->current->text);
	LCD_setCoursor(menu->lcd, 0, 1);
	if(menu->current->next != 0) {
		if(menu->current->next->child != NULL)
			LCD_writeCharacter(menu->lcd, '+');
		LCD_writeText(menu->lcd, menu->current->next->text);
    }
	else
		LCD_writeText(menu->lcd, "###END###");

}

void menu_nextItem(Menu *menu) {
    if (menu->current->next != 0) {
        menu->current = menu->current->next;
    }
}

void menu_prevItem(Menu *menu) {
    if (menu->current->prev != 0) {
        menu->current = menu->current->prev;
    }
}

void moveToChild(Menu *menu) {
    if(menu->current->child != 0) {
        menu->current = menu->current->child;
    }
}

void moveToParent(Menu *menu) {
	if(menu->current->parent != 0) {
		menu->current = menu->current->parent;
	}
}

void menu_actionForward(Menu *menu) {
    if (menu != 0 && menu->current != 0 && menu->current->actionForward != 0) {
        menu->current->actionForward(menu);
    }
}

void menu_actionBackward(Menu *menu) {
    if (menu != 0 && menu->current != 0 && menu->current->actionBackward != 0) {
        menu->current->actionBackward(menu);
    }
}






volatile uint8_t IsrKbdRunning = 0;
volatile char lastKeyPressed = 0;


volatile uint8_t stopwatchRunning = 0;
volatile uint32_t stopwatchTime = 0;
volatile uint8_t halfSecondCounter = 0;

volatile uint8_t blinker = 0;

void foo1(Menu *menu)
{
	LCD_clear(menu->lcd);
	LCD_writeText(menu->lcd, "Hold Clear to escape");
	IsrKbdRunning = 1;

	while(1){
		if(lastKeyPressed){
			if (lastKeyPressed == 'C')
				break;
			LCD_clear(menu->lcd);
			char displayString[2] = {lastKeyPressed, '\0'};
			LCD_writeText(menu->lcd, displayString);

			lastKeyPressed = 0;
		}
	}

	IsrKbdRunning = 0;
	lastKeyPressed = 0;




}

void timer0_init(){
    //  Timer0 Conf
    TCCR0 |= (1 << WGM01); //CTC
    OCR0 = 100;
    TIMSK |= (1 << OCIE0); 
    TCCR0 |= (1 << CS02) | (1 << CS00); // Prescaler 1024
}


ISR(TIMER0_COMP_vect) {
	if(IsrKbdRunning){
  	   	 lastKeyPressed = 0;
        PORTA |= 0xF0;

        PORTA &= ~(1 << 4);

        _delay_us(10);

        uint8_t rows = PINA & 0x0F; // Read all row states


        if (!(rows & (1 << 0))) lastKeyPressed = '1';
        else if (!(rows & (1 << 1))) lastKeyPressed = '4';
        else if (!(rows & (1 << 2))) lastKeyPressed = '7'; 
        else if (!(rows & (1 << 3))) lastKeyPressed = 'C'; 

        PORTA |= (1 << 4);

		}
}

void foo2_1(Menu *menu){
	LCD_clear(menu->lcd);
	LCD_writeText(menu->lcd, "Hold Clear to escape");
	blinker = 1;
	while(1){
		if (get_key('m', 'A') == 4)
			break;
	}
	blinker = 0;
	PORTD = (0 << PD0);



}
void foo2_2(Menu *menu)
{

	LCD_clear(menu->lcd);

		char lastKey;

    while (1) 
    {
		 char key = get_key('d', 'A');

		 if (halfSecondCounter == 0){
		    char timeString[16];
            sprintf(timeString, "Time: %02lu s", stopwatchTime);
		    LCD_clear(menu->lcd);
			LCD_writeText(menu->lcd, timeString);
			}
		 

		 switch (key) {
            case 2: // Start / stop
				stopwatchRunning = !stopwatchRunning;
                break;
			case 16: // Exit
				stopwatchTime = 0;
            	halfSecondCounter = 0;
				stopwatchRunning = 0;
				return;
            case 6: // Reset
				stopwatchTime = 0;
            	halfSecondCounter = 0;

                break;
       			 }
		lastKey = key;
		
		
	}


}

void timer2_init(){

    TCCR2 |= (1 << WGM21);
    OCR2 = 244;
    TIMSK |= (1 << OCIE2);
    TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);


}


ISR(TIMER2_COMP_vect) {
	if(blinker)
		PORTD ^= (1 << PD0);


	 if (++halfSecondCounter >= 2) { // 2 interupts = 1 sec
        halfSecondCounter = 0;
        if (stopwatchRunning) {
            stopwatchTime++;
			

        }
    }

}


void foo3(Menu *menu)
{
	LCD_clear(menu->lcd);
	LCD_writeText(menu->lcd, "Hold Clear to escape");
	while(1){
		if (get_key('m', 'A') == 4)
			break;
        for (uint8_t i = 0; i < 7; ++i) {
            PORTD = (1 << i) | (1 << (i + 1));
            _delay_ms(200);
        }

        // Move the snake backward
        for (int8_t i = 6; i > 0; --i) {
            PORTD = (1 << i) | (1 << (i - 1)); 
            _delay_ms(200);
        }
	}
	PORTD =0x00;
}


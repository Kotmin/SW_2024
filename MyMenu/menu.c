#include "menu.h"
#include "lcd_lib.h"
#include <string.h>


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
    option1_2.actionForward = NULL;
    option1_2.actionBackward = &moveToParent;

    // ================== option 2_1 ==================
    strcpy(option2_1.text,"Program 2_1");
    option2_1.next = &option2_2;
    option2_1.prev = NULL;
    option2_1.child = NULL;
    option2_1.parent = &option2;
    option2.child = &option2_1; // link parent
    option2_1.actionForward = NULL;
    option2_1.actionBackward = &moveToParent;

    // ================== option 2_2 ==================
    strcpy(option2_2.text,"Program 2_2");
    option2_2.next = NULL;
    option2_2.prev = &option2_1;
    option2_2.child = NULL;
    option2_2.parent = &option2;
    option2_2.actionForward = &moveToChild;
    option2_2.actionBackward = &moveToParent;

	    // ================== option 3_1 ==================
    strcpy(option3_1.text,"Program 3_1");
    option3_1.next = &option3_2;
    option3_1.prev = NULL;
    option3_1.child = NULL;
    option3_1.parent = &option3;
    option3.child = &option3_1; // link parent
    option3_1.actionForward = moveToChild;
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

void foo1(Menu *menu)
{
	LCD_clear(menu->lcd);
	LCD_writeText(menu->lcd, "Hold 1 to escape");
	while(1){
		if (get_key('m', 'A') == 1)
			break;
        for (uint8_t i = 0; i < 7; ++i) {
            PORTD = (1 << i) | (1 << (i + 1)); // Light up two adjacent LEDs
            _delay_ms(200);
        }

        // Move the snake backward
        for (int8_t i = 6; i > 0; --i) {
            PORTD = (1 << i) | (1 << (i - 1)); // Light up two adjacent LEDs
            _delay_ms(200);
        }
	}
	PORTD =0x00;
}

#ifndef MENU_H_
#define MENU_H_

#include "lcd_lib.h"
#include <stdint.h>

#include <avr/io.h>
#include <stdio.h>

#define MAX_MENU_ITEMS 10
#define MAX_MENU_LENGTH 16
#define MAX_MENUS 5 // Maximum number of different menus


typedef struct MenuStruct Menu;

typedef struct MenuItem {
    char text[MAX_MENU_LENGTH + 1];
    struct MenuItem *prev;
    struct MenuItem *next;
    struct MenuItem *child;
    struct MenuItem *parent;
    void (*actionForward)(Menu*);
    void (*actionBackward)(Menu*);
} MenuItem;

struct MenuStruct {
    MenuItem *current;
    LCD *lcd;
};

void menu_init(Menu *menu, LCD *lcd);
void menu_display(Menu *menu);
void menu_nextItem(Menu *menu);
void menu_prevItem(Menu *menu);
void menu_actionForward(Menu *menu);
void menu_actionBackward(Menu *menu);

// default actions
void moveToChild(Menu *menu);
void moveToParent(Menu *menu);

void foo1(Menu *menu);

// Menu items
extern MenuItem option1, option2, option3;
extern MenuItem option1_1, option1_2;
extern MenuItem option2_1, option2_2;



#endif /* MENU_H_ */

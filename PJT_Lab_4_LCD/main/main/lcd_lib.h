/*
 * lcd_lib.h
 *
 * Created: 04.11.2022 16:32:30
 *  Author: Student_PL
 */ 





#ifndef LCD_LIB_H_
#define LCD_LIB_H_

#include <avr/io.h>

#include <util/delay.h>
#include<string.h>


#define F_CPU 1000000UL
#define LCD_RS 1
#define LCD_E  0

typedef struct {
	volatile uint8_t *DDR;
	volatile uint8_t *PORT;
	} LCD_DISP;

extern void LCD_init(char port_nam,LCD_DISP *stru);
extern void setDDR(const char char_rep_of_port,LCD_DISP *stru);

extern void LCD_write(char *s,LCD_DISP *stru); 
extern void LCD_write_char(char b,LCD_DISP *stru); //parse char to place pointed with coursor

extern void LCD_clear(LCD_DISP *stru); //clear whole display
extern void LCD_set_coursor(unsigned char x, unsigned char y,LCD_DISP *stru);  //set coursor pos to x,y coordinates values=(0-15)
extern void LCD_clear_from_point(uint8_t x,uint8_t y,LCD_DISP *stru); // takes an integer value which point to specific cell number(0-31)








#endif /* LCD_LIB_H_ */
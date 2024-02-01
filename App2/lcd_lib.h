#ifndef LCD_LIB_H_
#define LCD_LIB_H_

#include <avr/io.h>
#include <util/delay.h>

// LCD Control Pins
#define LCD_RS   1
#define LCD_E    0

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
} LCD;

void LCD_init(LCD *lcd, char port);
void LCD_clear(LCD *lcd);
void LCD_clearFromPoint(LCD *lcd, uint8_t x, uint8_t y);
void LCD_writeCharacter(LCD *lcd, char c);
void LCD_writeText(LCD *lcd, char *text);
void LCD_setCoursor(LCD *lcd, uint8_t x, uint8_t y);
void LCD_sendInstruction(LCD *lcd, uint8_t cmd);

#endif /* LCD_LIB_H_ */

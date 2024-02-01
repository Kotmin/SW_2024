#include "lcd_lib.h"
#include <string.h>


void setDDR(LCD *lcd, char port) {
    switch (port) {
        case 'A': lcd->ddr = &DDRA; lcd->port = &PORTA; break;
        case 'B': lcd->ddr = &DDRB; lcd->port = &PORTB; break;
		case 'C': lcd->ddr = &DDRC; lcd->port = &PORTC; break;
		case 'D': lcd->ddr = &DDRD; lcd->port = &PORTD; break;
    }
    *(lcd->ddr) = 0xFF; // Set as output
}


void LCD_send4BitCommand(LCD *lcd, char command) {
    *(lcd->port) |= _BV(LCD_E); // Enable high
    // Send high nibble
    *(lcd->port) = (*(lcd->port) & 0x0F) | (command & 0xF0);
    *(lcd->port) &= ~_BV(LCD_E); // Enable low
    _delay_us(1);
}

void LCD_init(LCD *lcd, char port) {
    setDDR(lcd, port);
    _delay_ms(20); // Wait for more than 15ms after VCC rises to 4.5V

    // Set to 4-bit mode
    LCD_send4BitCommand(lcd, 0x30);
    _delay_ms(5);
    LCD_send4BitCommand(lcd, 0x30);
    _delay_us(100);
    LCD_send4BitCommand(lcd, 0x30);
    _delay_us(100);
    LCD_send4BitCommand(lcd, 0x20);
    _delay_us(100);

    LCD_sendInstruction(lcd, 0x28); // Function Set: 4-bit, 2 Line, 5x8 dots
    LCD_sendInstruction(lcd, 0x0C); // Display ON, Cursor OFF, Blink OFF
    LCD_clear(lcd); // Clear Display
    LCD_sendInstruction(lcd, 0x06); // Entry Mode: Increment cursor, No shift
}

void LCD_clear(LCD *lcd) {
    LCD_sendInstruction(lcd, 0x01); // Clear display command
    _delay_ms(2); // Clearing delay
}

void LCD_clearFromPoint(LCD *lcd, uint8_t x, uint8_t y) {
    LCD_setCoursor(lcd, x, y);
    for (uint8_t i = x; i < 16; i++) {
        LCD_writeCharacter(lcd, ' ');
    }
}

void LCD_writeCharacter(LCD *lcd, char c) {
    *(lcd->port) |= _BV(LCD_RS); // RS high for data
    LCD_send4BitCommand(lcd, c & 0xF0); // Send high nibble
    LCD_send4BitCommand(lcd, c << 4); // Send low nibble
    _delay_us(40);
}

void LCD_writeText(LCD *lcd, char *text) {
    for (uint8_t i = 0; text[i] != '\0'; i++) {
        if (i == 16) LCD_sendInstruction(lcd, 0xC0); // Move to next line
        LCD_writeCharacter(lcd, text[i]);
    }
}

void LCD_setCoursor(LCD *lcd, uint8_t x, uint8_t y) {
    uint8_t address = (y * 0x40 + x) | 0x80;
    LCD_sendInstruction(lcd, address);
}

void LCD_sendInstruction(LCD *lcd, uint8_t cmd) {
    *(lcd->port) &= ~_BV(LCD_RS); // RS low for instruction
    LCD_send4BitCommand(lcd, cmd & 0xF0); // Send high nibble
    LCD_send4BitCommand(lcd, cmd << 4); // Send low nibble
    _delay_us(40);
}

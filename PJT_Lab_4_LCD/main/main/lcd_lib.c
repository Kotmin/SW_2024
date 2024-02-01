/*
 * lcd_lib.c
 *
 * Created: 04.11.2022 16:32:46
 *  Author: Student_PL
 */ 

#include "lcd_lib.h"

void setDDR(const char char_rep_of_port,LCD_DISP *stru)
{
	switch (char_rep_of_port)
	{
		case 'A':
		stru->DDR = &DDRA;
		stru->PORT = &PORTA;
		break;
		case 'B':
		stru->DDR = &DDRB;
		stru->PORT = &PORTB;
		break;
		case 'C':
		stru->DDR = &DDRC;
		stru->PORT = &PORTC;
		break;
		case 'D':
		stru->DDR = &DDRD;
		stru->PORT = &PORTD;
		break;
	}
	*(stru->DDR) = 0xFF;
}
	
void LCD_init(char port_name,LCD_DISP *stru)
{		setDDR(port_name,stru);

	
		*(stru->DDR) = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_E)); // ustawienie kierunku wyjsciowego dla wszystkich linii
		*(stru->PORT) = 0; // ustawienie poczatkowego stany niskiego na wszystkich liniach
		*(stru->PORT) &= ~(_BV(LCD_RS));
		// ustawienie param. wy?ietlacza
		// bit4: 1 - 8 linii, 0-4 linii
		// bit3: 1-2 wiersze, 0-1 wiersz
		// bit2: 0-wymair znaku 5x8, 1 - wymiar 5x10
		LCD_write_char(0b00101000,stru);
		*(stru->PORT) |= _BV(LCD_RS);
		*(stru->PORT) |= _BV(LCD_RS);
		// bit2 - tryb pracy wy?ietlacza
		// bit1: 1 - przesuniecie okna, 0 przesuniecie kursora
		LCD_write_char(0b00000110,stru);
		*(stru->PORT) |= _BV(LCD_RS);
		*(stru->PORT) &= ~(_BV(LCD_RS));
		// bit2: 1 - wy?ietlacz wlaczany, 0 wylaczony
		// bit1: 1 - wlaczenie wyswietlacza kursora, 0 - kursor niewidoczny
		// bit0: 1 - kursor miga, 0 - kursor nie miga
		LCD_write_char(0b00001100,stru);
		*(stru->PORT) |= _BV(LCD_RS);
		
		LCD_clear(stru);
	
	
}

 void LCD_clear(LCD_DISP *stru)
 {
	 	*(stru->PORT) &= ~(_BV(LCD_RS)); // przestawia na linii RS wartosc na 0 po to by wyslac komende a nie dane
	    LCD_write_char(0x01,stru); // wysy?my polecenie wyczyszzcenia
	    *(stru->PORT) |= _BV(LCD_RS);
	    _delay_ms(60);
 }
 
 void LCD_write_char(char b,LCD_DISP *stru)
 {
	 
	 
	 	*(stru->PORT) |= _BV(LCD_E); // w?czenie linii enable
	 	*(stru->PORT) = (b & 0XF0)|(*(stru->PORT) & 0X0F); // wys?nie 4 starszych bit?
	 	*(stru->PORT) &= ~(_BV(LCD_E)); // potwierzdzenie wys?nia danych poprzez opadniecie ENABLE
	 	asm volatile("nop");
	 	*(stru->PORT) |= _BV(LCD_E);
	 	*(stru->PORT) = ((b & 0x0F) << 4)|(*(stru->PORT) & 0x0F); // wys?nie 4 m?dszych bit?
	 	*(stru->PORT) &= ~(_BV(LCD_E));
	 	_delay_us(50); // odczekanie czasy na potwierdzenie wyslanych danych
	 
 }
 
 void LCD_set_coursor(unsigned char x, unsigned char y,LCD_DISP *stru) //x i y //set LCD//y i x
 {
	 *(stru->PORT) &= ~(_BV(LCD_RS));
	 _delay_ms(5);
	 LCD_write_char((y*0x40+x)|0x80,stru);
	 *(stru->PORT) |= _BV(LCD_RS);
	 _delay_ms(5);
 }
 
 void LCD_clear_from_point(uint8_t x,uint8_t y,LCD_DISP *stru)
 {		
	LCD_set_coursor(x,y,stru);
	
	uint8_t i = 0;
	while(i<16)
	{
		LCD_write_char(' ',stru);
		i++;
	}
	 
 }
 
 
 void LCD_write(char *s,LCD_DISP *stru)
 {
	 while(*s)
	 {
		 LCD_write_char(*s,stru);
		 s++;
	 }
 }
 
 
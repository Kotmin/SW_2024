/*
 * main.c
 *
 * Created: 28.10.2022 16:31:46
 * Author : Student_PL
 
 tylko projekty slemy z jakimis komentarzami
 */ 



#include <avr/io.h>

#include <util/delay.h>
#include<string.h> 

#include "lcd_lib.h"

/*
#define F_CPU 1000000L



#define LCD_DDR  DDRB		
#define LCD_PORT PORTB		
#define LCD_RS 1			
#define LCD_E  0

//potem extern dodac!!! i volatile przy zmiennyhc


void LCD_init(char port_name){
	LCD_DDR = (0xF0)|(_BV(LCD_RS))|(_BV(LCD_E)); // ustawienie kierunku wyjsciowego dla wszystkich linii
	LCD_PORT = 0; // ustawienie poczatkowego stany niskiego na wszystkich liniach
	LCD_PORT &= ~(_BV(LCD_RS));
	// ustawienie param. wyietlacza
	// bit4: 1 - 8 linii, 0-4 linii
	// bit3: 1-2 wiersze, 0-1 wiersz
	// bit2: 0-wymair znaku 5x8, 1 - wymiar 5x10
	LCD_write_char(0b00101000);
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT |= _BV(LCD_RS);
	// bit2 - tryb pracy wyietlacza
	// bit1: 1 - przesuniecie okna, 0 przesuniecie kursora
	LCD_write_char(0b00000110);
	LCD_PORT |= _BV(LCD_RS);
	LCD_PORT &= ~(_BV(LCD_RS));
	// bit2: 1 - wyietlacz wlaczany, 0 wylaczony
	// bit1: 1 - wlaczenie wyswietlacza kursora, 0 - kursor niewidoczny
	// bit0: 1 - kursor miga, 0 - kursor nie miga
	LCD_write_char(0b00001100);
	LCD_PORT |= _BV(LCD_RS);
	
	LCD_clear_y();
}

void LCD_write_char(char b){
	LCD_PORT |= _BV(LCD_E); // w章czenie linii enable
	LCD_PORT = (b & 0XF0)|(LCD_PORT & 0X0F); // wys豉nie 4 starszych bit闚
	LCD_PORT &= ~(_BV(LCD_E)); // potwierzdzenie wys豉nia danych poprzez opadniecie ENABLE
	asm volatile("nop");
	LCD_PORT |= _BV(LCD_E);
	LCD_PORT = ((b & 0x0F) << 4)|(LCD_PORT & 0x0F); // wys豉nie 4 m這dszych bit闚
	LCD_PORT &= ~(_BV(LCD_E));
	_delay_us(50); // odczekanie czasy na potwierdzenie wyslanych danych
}

void LCD_write(char *s)
{
	while(*s)
	{
		LCD_write_char(*s);
		s++;
	}
}

//void LCD_clear_y();
void LCD_clear_y(){
	    LCD_PORT &= ~(_BV(LCD_RS)); // przestawia na linii RS wartosc na 0 po to by wyslac komende a nie dane
	    LCD_write_char(0x01); // wysy豉my polecenie wyczyszzcenia
	    LCD_PORT |= _BV(LCD_RS);
	    _delay_ms(60);
}


//void LCD_clear_y()
void LCD_clear_from_point(uint8_t point)
{		if (point >= 16)
	{	point %=16;
		LCD_set_coursor(point,1);
	}
		LCD_set_coursor(point,0);
		LCD_write("                ");	
}
void LCD_set_coursor(unsigned char x, unsigned char y) //x i y //set LCD//y i x
{
	    LCD_PORT &= ~(_BV(LCD_RS));
		_delay_ms(5);
	    LCD_write_char((y*0x40+x)|0x80);
	    LCD_PORT |= _BV(LCD_RS);
	    _delay_ms(5);
}
*/
int main(void)
{
    /* Replace with your application code */
	
	//char tekst[] = {'H','e','l','l','o'};
		
		
	char *tekst="Dzisiaj piatek";
	/*
	char *tekst2="byl";
		
	LCD_init(LCD_PORT);
	LCD_set_coursor(0,1);
	LCD_write(tekst);
	
	*/
	//LCD_set_coursor(0,1);
	//LCD_write(tekst2);
	
	LCD_DISP dsp;
	
	LCD_init('B',&dsp);
	LCD_clear(&dsp);
	LCD_set_coursor(0,0,&dsp);

	//LCD_clear_from_point(0,&dsp);
		LCD_write_char('A',&dsp);
		LCD_write_char('c',&dsp);
		LCD_write_char('b',&dsp);
		LCD_set_coursor(0,1,&dsp);
		
	LCD_write(tekst,&dsp);
	_delay_ms(500);
	LCD_clear_from_point(3,1,&dsp);

	
    while (1) 
    {
    }
}
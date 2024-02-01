
#ifndef MY_KEYBOARD_LIB_H_
#define MY_KEYBOARD_LIB_H_

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <util/delay.h>


extern void set_DDR(char port_name); // tylko  capital char dla nazw portu 'A','B','C','D'


extern int8_t get_key(const char typ, const char port_name); //typ - pierwsze litery od duza/mala 



extern int8_t getPin(const char port_name);
extern void setPort(const char port_name, int8_t state);

extern int8_t translate(int key_rcode);

#endif /* MY_KEYBOARD_LIB_H_ */

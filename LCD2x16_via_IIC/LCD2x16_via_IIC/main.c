/*
 * LCD2x16_via_IIC.c
 *
 * Created: 08.06.2020 11:23:57
 * Author : Robert
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD_HD44780_IIC.h"

int main(void)
{
	char data[20] = "napis testowy"; 
	unsigned char i = 0x30;
	/*
	DDRD |= 0x40;
	PORTD |= 0x40;
	
	_delay_ms(50);
	PORTD &= ~0x40;*/
	LCDinit();
	LCDhome();
	
	LCDstring(data, 13);
	
	LCDGotoXY(0,1);
	LCDstring("Ala ma kota", 11);
	LCDGotoXY(0,1);
	LCDstring("xD", 2);
	LCDcursorRight(11);
	_delay_ms(2000);
	LCDstring("xD", 2);
	_delay_ms(2000);
	LCDshiftRight(4);
	_delay_ms(2000);
	LCDshiftLeft(4);
    /* Replace with your application code */
    while (1) 
    {
    }
}


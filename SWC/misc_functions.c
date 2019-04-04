/*
 * misc_functions.c
 *
 * Created: 30.03.2019 13:31:05
 *  Author: Ole Hannemann
 */ 

#include "misc_functions.h"
#include <avr/io.h>


void port_config(){
	
	
	PORTB = 0b11111111;
	PORTC = 0b00001111;
	
	
	
}
uint8_t graytobcd(uint8_t graycode){

		uint8_t returnvalue = graycode & 0b00001000;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000100;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000010;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000001;
		return returnvalue;
		
}
void timer_config(){


	//8 bit Timer 0 config
	//ctc mode and 64 as prescaler
	TCCR0A = 0 | (1<<WGM01) /*| (1<<COM0A1) */| (1<<CS01) | (1<<CS00);
	TIMSK0 = 0 | (1<<OCF0A); //compare interrupt enable
	OCR0A = 250-1; // compare value for 1ms;

}
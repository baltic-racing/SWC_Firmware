/*
 * system_config.c
 *
 * Created: 28.04.2023 18:03:21
 *  Author: Julian Paskert
 */ 

#include <avr/io.h>
#include "system_config.h"
unsigned long system_time = 0;
unsigned long system_time_extended = 0;


void port_config(){
	
	//Buttons Left(PA0)/Right(PA1), Switches 1-4 (PA2-5)
	DDRA = 0;
	PORTA = 0xff;
	//D1_Fault red led (PC0) | D2_Heart blue led (PC2)
	DDRC |= (1<<PC0) | (1<<PC2);
	//Rotary encoders
	DDRB = 0;
	PORTB = 0xff;

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

void toggle_BL(){
	//toggles state of blue heart LED
	PORTC ^= (1<<PC2);
}

ISR(TIMER0_COMP_vect){
		
	system_time++; //system time generation
}
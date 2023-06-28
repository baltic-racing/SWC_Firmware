/*
 * system_config.h
 *
 * Created: 28.04.2023 18:04:09
 *  Author: Julian Paskert
 */ 


#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void timer_config();

uint8_t graytobcd(uint8_t graycode);

void port_config();

void toggle_BL(); //toggles state of blue heart LED

ISR(TIMER0_COMP_vect);
		

#endif /* SYSTEM_CONFIG_H_ */
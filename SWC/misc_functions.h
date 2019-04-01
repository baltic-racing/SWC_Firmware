/*
 * misc_functions.h
 *
 * Created: 29.03.2019 23:35:06
 *  Author: Ole Hannemann
 */ 

#include <avr/io.h>
#ifndef MISC_FUNCTIONS_H_
#define MISC_FUNCTIONS_H_

void port_config();
uint8_t graytobcd(uint8_t graycode);
void timer_config();



#endif /* MISC_FUNCTIONS_H_ */
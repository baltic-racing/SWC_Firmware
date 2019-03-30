/*
 * misc_functions.c
 *
 * Created: 30.03.2019 13:31:05
 *  Author: Ole Hannemann
 */ 

#include "misc_functions.h"

void portconfig(){
	
	
	
}
uint8_t graytobcd(uint8_t graycode){

		uint8_t returnvalue = graycode & 0b00001000;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000100;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000010;
		returnvalue |= (graycode ^ (returnvalue >> 1)) & 0b00000001;
		return returnvalue;
		
}
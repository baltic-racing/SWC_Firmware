/*
 * SWC.c
 *
 * Created: 29.03.2019 23:34:22
 * Author : Ole Hannemann
 */ 

#include "misc_functions.h"
#include <avr/interrupt.h>
#include "canlib.h"


unsigned long time=0;
unsigned long time_old_10 = 0;
struct CAN_MOB mob_to_transmit;

void read_inputs();



int main(void){
    
	port_config();
	timer_config();
	can_cfg();
	mob_to_transmit.mob_id = 0x100;
	mob_to_transmit.mob_idmask = 0;
	mob_to_transmit.mob_number = 0;
	
    while (1){
		
		if((time-time_old_10)>=10){
			read_inputs();
			can_tx(&mob_to_transmit);
			
			
		}
	}
}


void read_inputs(){
	
	mob_to_transmit.data_bytes[0] = graytobcd((~PINB)&0b00001111);
	mob_to_transmit.data_bytes[1] = graytobcd((~PINB)>>4);
	mob_to_transmit.data_bytes[2] = (((~PINC)>>PC0)&1);
	mob_to_transmit.data_bytes[3] = (((~PINC)>>PC1)&1);
	mob_to_transmit.data_bytes[4] = (((~PINC)>>PC2)&1);
	mob_to_transmit.data_bytes[5] = (((~PINC)>>PC3)&1);
	
}


ISR(TIMER0_COMP_vect){
		
	time++; //system time generation
	
}


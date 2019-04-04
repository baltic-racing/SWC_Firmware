/*
 * SWC.c
 *
 * Created: 29.03.2019 23:34:22
 * Author : Ole Hannemann
 */ 

#include "misc_functions.h"
#include <avr/interrupt.h>
#include "canlib.h"


volatile unsigned long system_time=0;
struct CAN_MOB mob_to_transmit;
uint8_t mob_0_data[8];

void read_inputs();



int main(void){
    
	port_config();
	timer_config();
	can_cfg();
	mob_to_transmit.mob_id = 0x100;
	mob_to_transmit.mob_idmask = 0;
	mob_to_transmit.mob_number = 0;
	
	sei();
	
    while (1){
		
		if(system_time > 10){
			system_time = 0;
			read_inputs();
			can_tx(&mob_to_transmit, mob_0_data);
		}
		
	}
}


void read_inputs(){
	
	mob_0_data[0] = graytobcd((~PINB)&0b00001111);
	mob_0_data[1] = graytobcd((~PINB)>>4);
	mob_0_data[2] = (((~PINC)>>PC0)&1);
	mob_0_data[3] = (((~PINC)>>PC1)&1);
	mob_0_data[4] = (((~PINC)>>PC2)&1);
	mob_0_data[5] = (((~PINC)>>PC3)&1);
	
}


ISR(TIMER0_COMP_vect){
		
	system_time++; //system time generation
	
}


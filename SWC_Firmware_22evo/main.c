/*
 * SWC_Firmware_22evo.c
 *
 * Created: 28.04.2023 17:29:57
 * Author : Julian Paskert
 */ 

#include <avr/io.h>
#include "system_config.h"
#include <avr/interrupt.h>
#include "canlib.h"


#define LEDRD (1<<PC0)
#define LEDBL (1<<PC2)

extern unsigned long system_time; //variable for system time, 1 = ca. 1ms
extern unsigned long system_time_extended; //variable used to extend system time in order to toggle Heart LED, 1 = 10*system_time

struct CAN_MOB mob_to_transmit;
uint8_t mob_0_data[8];

void read_inputs();

int main(void)
{
	sei(); //enables interrupts
    
	port_config();
	timer_config();
	
	can_cfg();
	//configure mob array
	mob_to_transmit.mob_id = 0x100;
	mob_to_transmit.mob_idmask = 0;
	mob_to_transmit.mob_number = 0;

    while (1) 
    {
		
		if(system_time > 10){
				//every 10ms the Controller becomes active...
				system_time = 0;
				read_inputs(); //saves input data to mob array
				can_tx(&mob_to_transmit, mob_0_data); //transmits collected data to Canbus	
				system_time_extended++;
				
				if(system_time_extended > 10){
					//toggles state of heart LED every 100ms
					toggle_BL();
					system_time_extended = 0;
				}
		}	
	 }
}

void read_inputs(){
	//Reads inputs of following buttons:...
	mob_0_data[0] = graytobcd((~PINB)&0b00001111); //Rotary Encoder left
	mob_0_data[1] = graytobcd((~PINB)>>4); //Rotary Encoder right
	mob_0_data[2] = (((~PINA)>>PA0)&1); //Push button left
	mob_0_data[3] = (((~PINA)>>PA1)&1); //Push button right
	mob_0_data[4] = (((~PINA)>>PA2)&1);	//Switch 1 (right)
	mob_0_data[5] = (((~PINA)>>PA3)&1); //Switch 2 (right)
	mob_0_data[6] = (((~PINA)>>PA4)&1); //Switch 3 (left)
	mob_0_data[7] = (((~PINA)>>PA5)&1); //Switch 4 (left)
}

/*
 * SWC_Firmware_22evo.c
 *
 * Created: 28.04.2023 17:29:57
 * Author : Julian Paskert
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "system_config.h"
#include "canlib.h"


#define LEDRD (1<<PC0)
#define LEDBL (1<<PC2)

extern unsigned long system_time; //variable for system time, 1 = ca. 1ms
extern unsigned long system_time_extended; //variable used to extend system time in order to toggle Heart LED, 1 = 10*system_time

void read_inputs();
struct CAN_MOB can_SWC_mob;
uint8_t SWC_databytes[8];

int main(void)
{
	sei(); //enables interrupts
    
	port_config();
	timer_config();
	can_cfg();

	
	can_SWC_mob.mob_id = 0x750;
	can_SWC_mob.mob_idmask = 0; //transmission needs no masking
	can_SWC_mob.mob_number = 0;

    while (1) 
    {
		
		if(system_time > 10){								//every 10ms the Controller becomes active... (100hz)
				system_time = 0;
				read_inputs();								 //saves input data to mob array	
				can_tx(&can_SWC_mob, SWC_databytes);		//transmits collected data to CAN bus
				system_time_extended++;
				
				if(system_time_extended > 10){
					toggle_BL();							//toggles state of heart LED every 100ms
					system_time_extended = 0;
				}
		}	
	 }
}

void read_inputs(){
	//Reads inputs of following buttons:...
	SWC_databytes[0] = graytobcd((~PINB)&0b00001111); //Rotary Encoder left
	SWC_databytes[1] = graytobcd((~PINB)>>4); //Rotary Encoder right
	SWC_databytes[2] = (((~PINA)>>PA0)&1); //Push button left
	SWC_databytes[3] = (((~PINA)>>PA1)&1); //Push button right
	SWC_databytes[4] = (((~PINA)>>PA2)&1);	//Switch 1 (right)
	SWC_databytes[5] = (((~PINA)>>PA3)&1); //Switch 2 (right)
	SWC_databytes[6] = (((~PINA)>>PA4)&1); //Switch 3 (left)
	SWC_databytes[7] = (((~PINA)>>PA5)&1); //Switch 4 (left)
}

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

/*struct CAN_MOB mob_to_transmit;
uint8_t mob_0_data[8];*/
struct CAN_MOB can_R2D_mob;
uint8_t R2D_databytes[8];

void read_inputs();

int main(void)
{
	sei(); //enables interrupts
    
	port_config();
	timer_config();
	
	can_cfg();
	//configure mob array
	/*mob_to_transmit.mob_id = 0x100;
	mob_to_transmit.mob_idmask = 0;
	mob_to_transmit.mob_number = 0;*/
	can_R2D_mob.mob_id = 0b100000000;
	can_R2D_mob.mob_idmask = 0;
	can_R2D_mob.mob_number = 0;

    while (1) 
    {
		
		if(system_time > 10){
				//every 10ms the Controller becomes active...
				system_time = 0;
				read_inputs(); //saves input data to mob array
				//can_tx(&mob_to_transmit, mob_0_data); //transmits collected data to Canbus	
				can_tx(&can_R2D_mob, R2D_databytes);
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
	R2D_databytes[0] = graytobcd((~PINB)&0b00001111); //Rotary Encoder left
	R2D_databytes[1] = graytobcd((~PINB)>>4); //Rotary Encoder right
	R2D_databytes[2] = (((~PINA)>>PA0)&1); //Push button left
	R2D_databytes[3] = (((~PINA)>>PA1)&1); //Push button right
	R2D_databytes[4] = (((~PINA)>>PA2)&1);	//Switch 1 (right)
	R2D_databytes[5] = (((~PINA)>>PA3)&1); //Switch 2 (right)
	R2D_databytes[6] = (((~PINA)>>PA4)&1); //Switch 3 (left)
	R2D_databytes[7] = (((~PINA)>>PA5)&1); //Switch 4 (left)
}

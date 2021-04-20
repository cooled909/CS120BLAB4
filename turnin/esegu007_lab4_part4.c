/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    enum STATE_MACHINE {SM_Start, SM_Lock, SM_A2Press, SM_A2Release, SM_Unlock} STATE;
    void Tick_Cnt(){
    	switch(STATE){
    		case SM_Start:
    		STATE = SM_Lock;
    		break;
    		case SM_Lock:
    		if(PINA == 0x04){
    			STATE = SM_A2Press;
    		}
    		break;
    		case SM_A2Press:
    		if(PINA == 0x00){
    			STATE = SM_A2Release;
    		}
    		else if (PINA == 0x04)
    		{
    			STATE = SM_A2Press;
    		}
    		else if(PINB == 0x00)
    		{
    			STATE = SM_Lock;
    		}
    		else if(PINB == 0x01){
    			STATE = SM_Unlock;
    		}
    		break;
    		case SM_A2Release:
    		if (PINA == 0x02 && PINB == 0x00)
    		{
    			STATE = SM_Unlock;
    		}
    		else if (PINA == 0x02 && PINB == 0x01)
    		{
    			STATE = SM_Lock;
    		}
    		else if (PINA == 0x00){
    			STATE = SM_A2Release;
    		}
    		else if(PINB == 0x00)
    		{
    			STATE = SM_Lock;
    		}
    		else if(PINB == 0x01){
    			STATE = SM_Unlock;
    		}
    		break;
    		case SM_Unlock:
    		if (PINA == 0x80)
    		{
    			STATE = SM_Lock;
    		}
    		else if(PINA == 0x04){
    			STATE = SM_A2Press;
    		}
    		break;
    		default:
    		STATE = SM_Lock;
    		break;
    	}
    	switch(STATE){
    		case SM_Lock:
    		PORTC = 0x00;
    		PORTB = 0x00;
    		break;
    		case SM_A2Press:
    		PORTC = 0x01;
    		break;
    		case SM_A2Release:
    		PORTC = 0x02;
    		break;
    		case SM_Unlock:
    		PORTC = 0x03;
    		PORTB = 0x01;
    		break; 
    		default:
    		break;
    	}
    }
    STATE = SM_Lock;
    while (1) {
    	Tick_Cnt();
    }
    return 1;
}
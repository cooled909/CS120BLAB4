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
    enum STATE_MACHINE {SM_Start, SM_Lock, SM_Press, SM_Release, SM_Unlock} STATE;
    enum STATE_MACHINE LASTSTATE;
    unsigned char combo[4] = {0x04, 0X01, 0x02, 0x01};
    unsigned char count;
    void Tick_Cnt(){
    	switch(STATE){
    		case SM_Start:
    		STATE = SM_Lock;
    		break;
    		case SM_Lock:
    		if(PINA != 0x00){
    			LASTSTATE = SM_Lock;
    			STATE = SM_Press;
    		}
    		break;
    		case SM_Press:
    		if(PINA == 0x00){
    			LASTSTATE = SM_Press;
    			STATE = SM_Release;
    		}
    		LASTSTATE = SM_Press;
    		break;
    		case SM_Release:
    		if (PINA == combo[count])
    		{
    			LASTSTATE = SM_Release;
    			STATE = SM_Press;
    		}
    		else if (count == sizeof(combo) && PINB == 0x00)
    		{
    			STATE = SM_Unlock;
    		}
    		else if (count == sizeof(combo) && PINB == 0x01)
    		{
    			STATE = SM_Lock;
    		}
    		break;
    		case SM_Unlock:
    		if (PINA == 0x80)
    		{
    			STATE = SM_Lock;
    		}
    		else if(PINA == combo[count]){
    			LASTSTATE = SM_Unlock;
    			STATE =  SM_Press;
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
    		count = 0x00;
    		break;
    		case SM_Press:
    		if(LASTSTATE != SM_Press){
    			count++;
    		}
    		PORTC = 0x01;
    		break;
    		case SM_Release:
    		PORTC = 0x02;
    		break;
    		case SM_Unlock:
    		count = 0;
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
/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 4  Exercise 2
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
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    enum STATE_MACHINE {SM_Start, SM_Wait, SM_A0, SM_A1, SM_Both, SM_Inc, SM_Dec, SM_Clr} STATE;
    void Tick_Cnt(){
    	switch(STATE){
    		case SM_Start:
    		STATE = SM_Wait;
    		break;
    		case SM_Wait:
    		if(PINA == 0x01){
    			STATE = SM_A0;
    		}
    		else if(PINA == 0x02){
    			STATE = SM_A1;
    		}
    		else if(PINA == 0x03){
    			STATE = SM_Both;
    		}
    		break;
    		case SM_A0:
    		if(PINA == 0x00){
    			STATE = SM_Inc;
    		}
    		else if(PINA == 0x03){
    			STATE = SM_Both;
    		}
    		break;
    		case SM_A1:
    		if(PINA == 0x00){
    			STATE = SM_Dec;
    		}
    		else if(PINA == 0x03){
    			STATE = SM_Both;
    		}
    		break;
    		case SM_Both:
    		if(PINA == 0x00){
    			STATE = SM_Clr;
    		}
    		break;
    		case SM_Inc:
    		STATE = SM_Wait;
    		break;
    		case SM_Dec:
    		STATE = SM_Wait;
    		break;
    		case SM_Clr:
    		STATE = SM_Wait;
    		break;
    		default:
    		STATE = SM_Wait;
    		break;
    	}
    	switch(STATE){
    		case SM_Start:
    		PORTC = 0x07;
    		break;
    		case SM_Inc:
    		if(PORTC >= 0x09){
    			break;
    		}
    		PORTC++;
    		break;
    		case SM_Dec:
    		if(PORTC <= 0x00){
    			break;
    		}
    		PORTC--;
    		break;
    		case SM_Clr:
    		PORTC = 0x00;
    		break; 
    		default:
    		break;
    	}
    }
    PORTC = 0x07;
    STATE = SM_Start;
    while (1) {
    	Tick_Cnt();
    }
    return 1;
}

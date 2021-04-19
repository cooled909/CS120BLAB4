/*	Author: Edward Segura
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 4  Exercise 1
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
    /* Insert your solution below */
    enum LIGHT_STATES {LS_Start, LS_B0, LS_B1} LIGHT_STATE;
    void Light_Contrl(){
    	switch(LIGHT_STATE){
    		case LS_Start:
    		LIGHT_STATE = LS_B0;
    		break;
    		case LS_B0:
    		if(PINA == 0x01){
    			LIGHT_STATE = LS_B1;
    		}
    		else{
    			LIGHT_STATE = LS_B0;
    		}
    		break;
    		case LS_B1:
    		if(PINA == 0x01){
    			LIGHT_STATE = LS_B0;
    		}
    		else{
    			LIGHT_STATE = LS_B1;
    		}
    		break;
    		default:
    		LIGHT_STATE = LS_B0;
    		break;
    	}
    	switch(LIGHT_STATE){
    		case LS_Start:
    		PORTB = 0x00;
    		case LS_B0:
    		PORTB = 0x01;
    		break;
    		case LS_B1:
    		PORTB = 0x02;
    		break; 
    		default:
    		break;
    	}
    }
    LIGHT_STATE = LS_Start;
    while (1) {
    	Light_Contrl();
    }
    return 1;
}

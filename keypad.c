/*
 * keypad.c
 *
 *  Created on: Sep 19, 2019
 *      Author: marim
 */

#include "keypad.h"
#if (KEYPAD_COLUMNS==3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8);
#elif (KEYPAD_COLUMNS==4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8);
#endif
uint8 Keypad_getPressedkey(void){
	uint8 i;
	uint8 j;
	while(1){
		for(i=0;i<KEYPAD_COLUMNS;i++){
        REG_DIRECTION=(0x10<<i);          //rows are inputs and each column will be output
        REG_OUTPUT= (~(0x10<<i)) ;  //activates the internal pull up in first 4 pins and the last 4 pins will be 1
			for(j=0;j<KEYPAD_ROWS;j++){
               if(BIT_IS_CLEAR(REG_INPUT,j)){
#if (KEYPAD_COLUMNS==3)
            	return   Keypad_4x3_adjustSwitchNumber((j*KEYPAD_COLUMNS)+i+1);
#elif (KEYPAD_COLUMNS==4)
            	return   Keypad_4x4_adjustSwitchNumber((j*KEYPAD_COLUMNS)+i+1);
#endif
               }
			}
		}
	}
}
#if (KEYPAD_COLUMNS==3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 num){
	switch(num){
	case 10:
			return '*';
			break;
	case 11:
			return 0;
			break;
	case 12:
			return '#';
			break;
	default:
		return num;
		break;
	}
}
#elif (KEYPAD_COLUMNS==4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 num){
    switch(num){
    case 1:
    		return 7;
    		break;
    case 2:
    		return 8;
    		break;
    case 3:
    		return 9;
    		break;
    case 4:
    		return '/';
    		break;
    case 5:
    		return 4;
    		break;
    case 6:
    		return 5;
    		break;
    case 7:
    		return 6;
    		break;
    case 8:
    		return '*';
    		break;
    case 9:
    		return 1;
    		break;
    case 10:
    		return 2;
    		break;
    case 11:
    		return 3;
    		break;
    case 12:
    		return '-';
    		break;
    case 13:
    		return num;
    		break;
    case 14:
    		return 0;
    		break;
    case 15:
    		return '=';
    		break;
    case 16:
    		return '+';
    		break;
    default:
    	return num;
    	break;
    }
}
#endif


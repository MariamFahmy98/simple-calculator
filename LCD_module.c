/*
 * LCD_module.c
 *
 *  Created on: Sep 18, 2019
 *      Author: marim
 */
#include"LCD_module.h"

void LCD_init(void){
     CONTROL_DIRECTION |= (1<<RS) | (1<<W) | (1<<E);
#if (LCD_MODE_BITS == 4)
     #ifdef HIGHER_PINS
     DATA_DIRECTION=0xf0;
     #else
     DATA_DIRECTION=0x0f;
     #endif
     LCD_sendCommand(SWITCH_TO_4BITS_MODE);
     LCD_sendCommand(BITS4_2LINES_COMMAND);
#elif(LCD_MODE_BITS == 8)
     DATA_DIRECTION=0xff;
     LCD_sendCommand(BITS8_2LINES_COMMAND);
#endif
     LCD_sendCommand(CLEAR_SCREEN);
     LCD_sendCommand(CURSOR_OFF);
}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(CONTROL_OUTPUT,RS);
	CLEAR_BIT(CONTROL_OUTPUT,W);
	_delay_us(1);
	SET_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#if (LCD_MODE_BITS == 4)
      #ifdef HIGHER_PINS
	DATA_OUTPUT= (DATA_OUTPUT & 0x0f) | (command & 0xf0);
      #else
	DATA_OUTPUT= (DATA_OUTPUT & 0xf0) | ((command & 0xf0) >>4);
      #endif
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
	SET_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
     #ifdef HIGHER_PINS
	DATA_OUTPUT= (DATA_OUTPUT & 0X0F) | ((command & 0x0f) <<4);
     #else
	DATA_OUTPUT= (DATA_OUTPUT & 0xf0) | (command & 0x0f);
     #endif
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#elif(LCD_MODE_BITS == 8)
	DATA_OUTPUT=command;
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#endif
}

void LCD_displayCharacter(uint8 character){
	SET_BIT(CONTROL_OUTPUT,RS);
	CLEAR_BIT(CONTROL_OUTPUT,W);
	_delay_us(1);
	SET_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#if (LCD_MODE_BITS == 4)
      #ifdef HIGHER_PINS
	DATA_OUTPUT= (DATA_OUTPUT & 0x0f) | (character & 0xf0);
      #else
	DATA_OUTPUT= (DATA_OUTPUT & 0xf0) | ((character & 0xf0) >> 4);
      #endif
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
	SET_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
     #ifdef HIGHER_PINS
	DATA_OUTPUT= (DATA_OUTPUT & 0x0f) | ((character & 0x0f) << 4);
     #else
	DATA_OUTPUT= (DATA_OUTPUT & 0xf0) |(character & 0x0f);
     #endif
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#elif(LCD_MODE_BITS == 8)
	DATA_OUTPUT=character;
	_delay_us(1);
	CLEAR_BIT(CONTROL_OUTPUT,E);
	_delay_us(1);
#endif
}

void LCD_displayString(const char* charPtr){
	while((*charPtr)!='\0'){
		LCD_displayCharacter(*charPtr);
		charPtr++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 column){
    uint8 address;
    switch(row){
    case 0:
        address=column;
        break;
    case 1:
    	address=column+0x40;
    	break;
    case 2:
    	address=column+0x10;
    	break;
    case 3:
    	address=column+0x50;
    	break;
    }
    LCD_sendCommand(address|CURSOR_TO_FIRST_LINE);
}

void LCD_displayStringRowColumn(uint8 row,uint8 column, const char *ptr){
     LCD_goToRowColumn(row,column);
     LCD_displayString(ptr);
}

void LCD_integerToString(int data){
       char buff[16];
       itoa(data,buff,10);
       LCD_displayString(buff);
}
void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_SCREEN);
}


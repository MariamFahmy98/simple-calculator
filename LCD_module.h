/*
 * LCD_module.h
 *
 *  Created on: Sep 18, 2019
 *      Author: marim
 */

#ifndef LCD_MODULE_H_
#define LCD_MODULE_H_

#include"standard_library.h"
#include"common_macros.h"
#include"AVR_configrations.h"

#define LCD_LINES 4
#define LCD_MODE_BITS 4

#define RS PB1
#define W PB2
#define E PB3
#define DATA_DIRECTION DDRD
#define DATA_OUTPUT PORTD
#define CONTROL_DIRECTION DDRB
#define CONTROL_OUTPUT PORTB

#define CLEAR_SCREEN 0x01
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define BITS8_2LINES_COMMAND 0x38
#define CURSOR_TO_FIRST_LINE 0x80
#define BITS4_2LINES_COMMAND 0x28
#define SWITCH_TO_4BITS_MODE 0x02

void LCD_init(void);
void LCD_sendCommand(uint8);
void LCD_displayCharacter(uint8);
void LCD_displayString(const char*);
void LCD_goToRowColumn(uint8,uint8);
void LCD_displayStringRowColumn(uint8,uint8,const char*);
void LCD_integerToString(int);
void LCD_clearScreen(void);

#endif /* LCD_MODULE_H_ */

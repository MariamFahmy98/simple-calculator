/*
 * keypad.h
 *
 *  Created on: Sep 19, 2019
 *      Author: marim
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "standard_library.h"
#include "common_macros.h"
#include "AVR_configrations.h"

#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4
#define REG_DIRECTION DDRA
#define REG_OUTPUT PORTA
#define REG_INPUT PINA

uint8 Keypad_getPressedkey(void);


#endif /* KEYPAD_H_ */

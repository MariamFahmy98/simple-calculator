/*
 * project.c
 *
 *  Created on: Sep 19, 2019
 *      Author: marim
 */

#include"LCD_module.h"
#include"keypad.h"
int main(void){
  uint8 keyPressed,value1,value2,operation;
  LCD_init();
  LCD_displayString("Welcome");
  LCD_goToRowColumn(1,0);
  uint8 count=0;
  while(1){
	  count++;
	  keyPressed=Keypad_getPressedkey();
	  		keyPressed = Keypad_getPressedkey();
	  		if((keyPressed <= 9) && (keyPressed >= 0))
	  		{
	  			LCD_integerToString(keyPressed);
	  			if(count==1){
	  				value1=keyPressed;
	  			}
	  			else if(count ==3){
	  				value2=keyPressed;
	  			}
	  		}
	  		else
	  		{
	  			LCD_displayCharacter(keyPressed); /* display the pressed keypad switch */
	  			if(count==2){
	  				operation=keyPressed;
	  			}
	  			else if(count==4){
	  				count=0;
	  				switch(operation){
	  				case'+':
	  					LCD_integerToString(value1+value2);
	  					break;
	  				case'-':
	  					LCD_integerToString(value1-value2);
	  					break;
	  				case'*':
	  					LCD_integerToString(value1*value2);
	  					break;
	  				case'/':
	  					LCD_integerToString(value1/value2);
	  					break;
	  				}
	  				_delay_ms(100000);
	  				LCD_clearScreen();
	  				continue;
	  			}
	  		}
	  		_delay_ms(500);
	      }
  }


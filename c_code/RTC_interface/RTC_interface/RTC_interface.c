/**
********************************************************************************
* @file   : RTC_interface.c
* @version: 1.0.1
* @author : Mohamed Yasser
* @brief  : Project based on I2C protocol, with single master and multi-slaves.
********************************************************************************
*/

/* Includes Section Start -------------------------------------*/
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"
#include "EEPROM.h"
#include "RTC.h"
#include "Keypad.h"
#include "LCD.h"
#include "typdef.h"
/* Includes Section End ---------------------------------------*/

/* Function Prototype Section Start ---------------------------*/
void print_key_num(uint8 key);
/* Function prototype section End ---------------------------*/

/* Global Variables Section Start -----------------------------*/
uint16 second, minute, hour, day, date, month, year;
uint8 key_buffer[6], callender_buffer[6], time_buffer[6], memory_read_buffer[18];
uint8 address_low, address_high;
uint16 memory_address;
uint8 one_byte_recievd, one_byte_send;
/* Global Variables Section End -------------------------------*/



/* Main Program Start -----------------------------------------*/
int main(void)
{
	I2C_Init();			/* Initialize bit rate of I2C */
	LCD_vInit();		/* Initialize LCD */
	keypad_vInit();		/* define keypad pins */
	uint8 button_val = 0xff; /* variable to store the pressed button value */
	
	while(1)
	{
		button_val = keypad_u8check_press(); /* read the pressed button */
		if (button_val != 0xff) /* a button is pressed */
		{
			if (button_val < 15)
			{
				LCD_vSend_cmd(CLR_SCREEN);
				print_key_num(button_val);
				key_buffer[0] = button_val;
				RTC_Read_Calendar(3, day, date, month, year);		/* Read the calender with day address i.e location is 3 */
				sprintf(callender_buffer, "%02x/%02x/20%02x", date, month, year);
				RTC_Read_Clock(0, second, minute, hour);		/* Read the clock with second address i.e location is 0 */
				sprintf(time_buffer, "%02x:%02x:%02x", (hour & 0b00011111), minute, second);
				_delay_ms(2000); /* display key number for 2 secs */
				
				/* now print date and time of press */
				LCD_vSend_cmd(CLR_SCREEN);
				LCD_vSend_string("Date");
				LCD_vSend_string(callender_buffer);
				LCD_movecursor(2,1);
				LCD_vSend_string("Time");
				LCD_vSend_string(time_buffer);
				_delay_ms(5);
				EEPROM_write(address_low, address_high, key_buffer);
				_delay_ms(5);
				memory_address += 6;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				EEPROM_write(address_low, address_high, callender_buffer);
				_delay_ms(5);
				memory_address += 6;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				EEPROM_write(address_low, address_high, time_buffer);
				_delay_ms(5);
				memory_address += 6;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
			}
			else if (button_val == 15) /* button '15' is pressed -> print last key */
			{
				/* Read data from EEPROM */
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				EEPROM_read(address_low, address_high, time_buffer);
				memory_address -= 6;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				EEPROM_read(address_low, address_high, callender_buffer);
				memory_address -= 6;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				EEPROM_read(address_low, address_high, key_buffer);
				/* print the restored data on LCD */
				LCD_vSend_cmd(CLR_SCREEN);
				LCD_vSend_string("Last key is=");
				LCD_vSend_char(key_buffer[0]+48);
				_delay_ms(2000); /* display key number for 2 secs */
				LCD_vSend_cmd(CLR_SCREEN);
				LCD_vSend_string("Date=");
				LCD_vSend_string(callender_buffer);
				LCD_movecursor(2,1);
				LCD_vSend_string("Time=");
				LCD_vSend_string(time_buffer);
			}
			else
			{
				/* Erase EEPROM */
				LCD_vSend_cmd(CLR_SCREEN);
				LCD_vSend_string("Clearing Mem...");
				memory_address = 0xff;
				address_low = (uint8) memory_address;
				address_high = (uint8) (memory_address >> 8u);
				uint16 page=0;
				for (page=0; page<1637; page++)
				{
					EEPROM_Erase_all_data(address_low, address_high);
					_delay_ms(100);
					memory_address+=64;
					address_low=(uint8)(memory_address);
					address_high=(uint8)(memory_address >> 8u);
				}
				LCD_vSend_cmd(CLR_SCREEN);
				LCD_vSend_string("All Data");
				LCD_movecursor(2,1);
				LCD_vSend_string("are deleted!");
			}
		}
		_delay_ms(250);
	} //end of while
}// end of main

/* Main Program End -------------------------------------------*/

/* Sub-program Section Start ----------------------------------*/
void print_key_num(uint8 key)
{
	LCD_vSend_cmd(CLR_SCREEN);
	LCD_vSend_string("Key = ");
	if (key <10)
	{
		LCD_vSend_char(48+key);
	}
	else
	{
		LCD_vSend_char(48+(key/10));
		LCD_vSend_char(48+(key%10));
	}
	
}
/* Sub-program Section End ------------------------------------*/


/**
*****************************************************************
* Revision Log
* Date			  By               Brief
* -------------   --------------   ----------------------------------
* 15-April-2022   Mohamed Yasser   created this project.
* -------------   --------------   ----------------------------------
*****************************************************************
*/
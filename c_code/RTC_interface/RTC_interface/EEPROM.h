/*
 * EEPROM.h
 *
 * Created: 3/18/2022 10:01:53 AM
 *  Author: Mohamed Yasser
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "typdef.h"
#define EEPROM_Slave_Address_Write 0xA0		/* Define EEPROM slave address for write operation */
#define EEPROM_Slave_Address_Read  0xA1		/* Define EEPROM slave address for read operation */

void EEPROM_write(uint8 address_low_byte, uint8 address_high_byte, uint8* buffer_data);
void EEPROM_read(uint8 address_low_byte, uint8 address_high_byte, uint8 *memory_ptr);
void EEPROM_Erase_all_data(uint8 address_low_byte, uint8 address_high_byte);


#endif /* EEPROM_H_ */
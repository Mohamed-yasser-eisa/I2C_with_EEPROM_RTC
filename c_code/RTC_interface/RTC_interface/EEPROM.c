/*
 * EEPROM.c
 *
 * Created: 3/18/2022 10:01:31 AM
 *  Author: Mohamed Yasser
 */ 

#include "EEPROM.h"
#include "I2C_Master_H_file.h"


void EEPROM_write(uint8 address_low_byte, uint8 address_high_byte, uint8* buffer_data)
{
	/* first we send address location to start write from */
	I2C_Start(EEPROM_Slave_Address_Write);
	I2C_Write(address_high_byte);
	I2C_Write(address_low_byte);
	/* now we are ready to write data */
	uint8 i=0;
	for (i=0; i<6; i++)
	{
		I2C_Write((uint8)*(buffer_data+i));
	}
	I2C_Stop();
	//address_low_byte+=6;
}

void EEPROM_Erase_all_data(uint8 address_low_byte,uint8 address_high_byte)
{
	/* first we send address location to start write from */
	I2C_Start(EEPROM_Slave_Address_Write);
	I2C_Write(address_high_byte);
	I2C_Write(address_low_byte);
	/* now we are ready to write data */
	uint8 i=0;
	for (i=0; i<64; i++) //write 0xFF on one page
	{
		I2C_Write(0xFF);
	}
	I2C_Stop();
}


void EEPROM_read(uint8 address_low_byte, uint8 address_high_byte, uint8 *memory_ptr)
{
	//address_low_byte-=18;
	I2C_Start(EEPROM_Slave_Address_Write);
	I2C_Write(address_high_byte);
	I2C_Write(address_low_byte);
	I2C_Repeated_Start(EEPROM_Slave_Address_Read);
	uint8 i=0;
	for (i=0; i<5; i++)
	{
		*(memory_ptr+i)=I2C_Read_Ack(); /* Read one byte at time */
	}
	*(memory_ptr+i)=I2C_Read_Nack();
	I2C_Stop();
}















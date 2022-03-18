/*
 * RTC.c
 *
 * Created: 3/18/2022 10:02:24 AM
 *  Author: Mohamed Yasser
 */ 

#include "typdef.h"
#include "RTC.h"
#include "I2C_Master_H_file.h"

void RTC_Read_Clock(uint8 read_clock_address,uint8* sec, uint8* min, uint8* hou)
{
	I2C_Start(RTC_Write_address);				/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);				/* Write address to read */
	I2C_Repeated_Start(RTC_Read_address);		/* Repeated start with device read address */

	*sec = I2C_Read_Ack();						/* Read second */
	*min = I2C_Read_Ack();						/* Read minute */
	*hou = I2C_Read_Nack();						/* Read hour with Nack */
	I2C_Stop();									/* Stop i2C communication */
}


void RTC_Read_Calendar(uint8 read_calendar_address, uint8* dy, uint8* de, uint8* moth, uint8* yr)
{
	I2C_Start(RTC_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(RTC_Read_address);

	*dy = I2C_Read_Ack();							/* Read day */
	*de = I2C_Read_Ack();							/* Read date */
	*moth = I2C_Read_Ack();							/* Read month */
	*yr = I2C_Read_Nack();							/* Read the year with Nack */
	I2C_Stop();										/* Stop i2C communication */
}
/*
bool IsItPM(uint8 hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}
*/










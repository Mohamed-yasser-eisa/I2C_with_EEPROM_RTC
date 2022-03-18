/*
 * RTC.h
 *
 * Created: 3/18/2022 10:02:10 AM
 *  Author: Mohamed Yasser
 */ 


#ifndef RTC_H_
#define RTC_H_

#define RTC_Write_address	0xD0		/* Define RTC slave address for write operation */
#define RTC_Read_address	0xD1		/* Define RTC slave address for read operation */
#define TimeFormat12		0x40		/* Define 12 hour format */
#define AMPM				0x20

void RTC_Read_Clock(uint8 read_clock_address,uint8* sec, uint8* min, uint8* hou);
void RTC_Read_Calendar(uint8 read_calendar_address, uint8* dy, uint8* de, uint8* moth, uint8* yr);
//bool IsItPM(uint8 hour_);

#endif /* RTC_H_ */
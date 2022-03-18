
#include "typdef.h"
#include "LCD.h"
#include "GPIO.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>

void LCD_vInit(void)
{
	_delay_ms(200);
	DIO_vsetPINDir('B',0,1);
	DIO_vsetPINDir('B',1,1);
	DIO_vsetPINDir('B',2,1);
	DIO_vsetPINDir('B',3,1);
	DIO_vsetPINDir('B',4,1);
	DIO_vsetPINDir('B',5,1);
	DIO_vsetPINDir('B',6,1);
	DIO_vsetPINDir('B',7,1);
	
	DIO_vsetPINDir('A',EN,1);
	DIO_vsetPINDir('A',RS,1);
	LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1); 
}


static void send_falling_edge(void)
{
	DIO_write('A',EN,1);
	_delay_ms(2);
	DIO_write('A',EN,0);
	_delay_ms(2);
}

void LCD_vSend_char(uint8 data)
{
	DIO_write_port('B',data);
	DIO_write('A',RS,1);
	send_falling_edge();
	_delay_ms(1);
}


void LCD_vSend_string(uint8 *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
}
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_movecursor(uint8 row,uint8 coloumn)
{
	uint8 data =0x00;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}

void LCD_vSend_cmd(uint8 cmd)
{
	DIO_write_port('B',cmd);
	DIO_write('A',RS,0);
	send_falling_edge();
	_delay_ms(1);
}
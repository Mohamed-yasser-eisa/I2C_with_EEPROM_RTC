

#include "typdef.h"
#include "Keypad.h"

 
 void keypad_vInit()
 {
	 DIO_vsetPINDir('C',4,1);
	 DIO_vsetPINDir('C',5,1);
	 DIO_vsetPINDir('C',6,1);
	 DIO_vsetPINDir('C',7,1);
	 DIO_vsetPINDir('D',4,0);
	 DIO_vsetPINDir('D',5,0);
	 DIO_vsetPINDir('D',6,0);
	 DIO_vsetPINDir('D',7,0);
 }
 char keypad_u8check_press()
 {
	 uint8 arr[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	 uint8 row,coloumn,x;
	 uint8 returnval=NOTPRESSED;
	 for(row=0;row<4;row++)
	 {
	 DIO_write('C',4,1);
	 DIO_write('C',5,1);
	 DIO_write('C',6,1);
	 DIO_write('C',7,1);
	 DIO_write('C',(row+4),0);
	
		for(coloumn=0;coloumn<4;coloumn++)
		{
		 x=DIO_u8read('D',(coloumn+4));
		 if(x==0)
			 {
			 returnval=arr[row][coloumn];
			 break;
			 }  
		}	
	 if(x==0)
		{
		 break;
		}
	 }	 
	 return returnval ;	 
 }
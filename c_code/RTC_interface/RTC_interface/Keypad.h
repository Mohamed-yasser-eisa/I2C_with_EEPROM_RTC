

#ifndef KEYPAD_H_
#define KEYPAD_H_


#define NOTPRESSED 0xff
#include "GPIO.h"
void keypad_vInit();
char keypad_u8check_press();


#endif /* KEYPAD_H_ */
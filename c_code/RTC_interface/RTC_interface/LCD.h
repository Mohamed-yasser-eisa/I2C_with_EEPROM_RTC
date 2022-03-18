

#ifndef LCD_H_
#define LCD_H_

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#define EN 6
#define RS 7

#define EIGHT_BITS 0x38

void LCD_vInit(void);
static void send_falling_edge(void);
void LCD_vSend_cmd(uint8 cmd);
void LCD_vSend_char(uint8 data);
void LCD_vSend_string(uint8 *data);
void LCD_clearscreen();
void LCD_movecursor(uint8 row,uint8 coloumn);





#endif /* LCD_H_ */
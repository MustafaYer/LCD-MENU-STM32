


#include "stm32f1xx_hal.h"

//#include "stdio.h"

#define LCD_ROWS 2
#define LCD_COLS 16
#define LCDC_SET_DDRAM				0x80
#define LCD_LINE1 		0x00
#define LCD_LINE2 		0x40
#define LCD_LINE3 		0x14
#define LCD_LINE4 		0x54

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);

void lcd_send_int(int number);

void lcd_clear (void);

void lcd_locate(uint8_t x, uint8_t y);

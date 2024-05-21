/*
 * LCD_BUF.h
 *
 *  Created on: May 18, 2024
 *      Author: musta
 */

#ifndef INC_LCD_BUF_H_
#define INC_LCD_BUF_H_

#define LCD_ROWS 2
#define LCD_COLS 16



void buf_char(char c);
void lcd_put_string(int row, int col, char* str);
void lcd_update();
void buf_clear();
void buf_locate(uint8_t x, uint8_t y);
void buf_str(char *text);
void buf_str_XY(uint8_t x, uint8_t y, char *text);
void lcd_refresh();
void buf_clear_menu();
void buf_int(uint8_t value);
#endif /* INC_LCD_BUF_H_ */

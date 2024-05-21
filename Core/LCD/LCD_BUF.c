/*
 * LCD_BUF.c
 *
 *  Created on: May 18, 2024
 *      Author: musta
 */

#include "i2c-lcd.h"
#include "LCD_BUF.h"
#include "stdlib.h"

char lcd_buffer[LCD_ROWS][LCD_COLS];
char 	lcd_buf_old[LCD_ROWS][LCD_COLS];

uint8_t lcd_buf_x, lcd_buf_y = 0;

void buf_locate(uint8_t x, uint8_t y) {
	lcd_buf_x = x;
	lcd_buf_y = y;
}

void buf_char(char c) {
    if (lcd_buf_x < LCD_ROWS && lcd_buf_y < LCD_COLS) {
        lcd_buffer[lcd_buf_x][lcd_buf_y] = c;
        lcd_buf_y++;
        if (lcd_buf_y == LCD_COLS) {
            lcd_buf_y = 0;
            lcd_buf_x++;
            if (lcd_buf_x == LCD_ROWS)
                lcd_buf_x = 0; // Satırın sonunda olduğunda sıfırla
        }
    }
}

void buf_clear_menu() {
    for (uint8_t x = 1; x < LCD_ROWS; x++) {
        for (uint8_t y = 0; y < LCD_COLS; y++) {
            lcd_buffer[x][y] = ' ';
        }
    }
    lcd_buf_x = 0; // Satır
    lcd_buf_y = 0; // Sütun
}


void lcd_refresh() { // Send LCD
    static uint8_t locate_flag = 0;

    for (uint8_t x = 0; x < LCD_ROWS; x++) {
        lcd_locate(x, 0); // Her satırın başına gidiyoruz

        for (uint8_t y = 0; y < LCD_COLS; y++) {
            if (lcd_buffer[x][y] != lcd_buf_old[x][y]) {
                if (!locate_flag) {
                    lcd_locate(x, y); // Satır ve sütunu ayarlıyoruz
                }
                lcd_send_data(lcd_buffer[x][y]);
                lcd_buf_old[x][y] = lcd_buffer[x][y];
                locate_flag = 1;
            } else {
                locate_flag = 0;
            }
        }
    }
}

void buf_clear() {
    for (uint8_t x = 0; x < LCD_ROWS; x++) {
        for (uint8_t y = 0; y < LCD_COLS; y++) {
            lcd_buffer[x][y] = ' ';
        }
    }
    lcd_buf_x = 0;
    lcd_buf_y = 0;
}


void buf_str_XY(uint8_t x, uint8_t y, char *text) {
	buf_locate(x, y);

	while (*text)
		buf_char(*text++);

}


void buf_str(char *text) {

	while (*text)
		buf_char(*text++);
}

void buf_int(uint8_t value) {

	char string[5];
	itoa(value, string, 10);
	buf_str(string);

}

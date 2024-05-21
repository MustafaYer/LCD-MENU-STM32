/*
 * BRIGHTNESS.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */

#include "MENU.h"
#include "main.h"
#include "i2c-lcd.h"
#include "BRIGTHNESS/BRIGHTNESS.h"
#include "LCD_BUF.h"
#include <string.h>

extern void (*key_next_func)();
extern void (*key_prev_func)();
extern void (*key_enter_func)();
extern void (*key_back_func)();

extern char lcd_buffer[LCD_ROWS][LCD_COLS];

extern menu_t *temp;
extern menu_t *currentPointer; // baslangicta ilk menuden baslar

void disp_brightness_next() {

	if (TIM4->CCR3 < 65000){
		TIM4->CCR3 += 6500;
	}

	disp_brightness_refresh();

}

void disp_brightness_prev() {

	if (TIM4->CCR3 >= 6500){
		TIM4->CCR3 -= 6500;
	}

	disp_brightness_refresh();

}

void disp_brightness_back() {

	key_next_func = menu_next;
	key_prev_func = menu_prev;
	key_enter_func = menu_enter;
	key_back_func = menu_back;

	menu_refresh();

}

void disp_brightness_refresh() {

	uint8_t percent = 0;

	percent = (TIM4->CCR3) / 650;
	if (percent < 11) {
		TIM4->CCR3 = 6500;
		percent = 10;
	}
	if (percent > 100) {
		TIM4->CCR3 = 100;
		percent = 100;
	}

	buf_clear_menu(); // bufferı temizle
	buf_locate(0, 3);
	buf_str(currentPointer->name); //BRIGHTNESS

	// Satır 1'de dolu olması gereken sütunları doldur
	for (uint8_t y = 5; y < (percent / 10) + 5; y++) {
		lcd_buffer[1][y] = 255; // 255 dolu karakteri temsil ediyor, bunu ekranınıza göre ayarlayabilirsiniz
	}

	// Yüzde sembolü ve yüzdelik değeri ekle
	buf_locate(1, 0);
	buf_str("%");
	buf_locate(1, 1);
	buf_int(percent);

}

void disp_brightness_callback() {

	key_next_func = disp_brightness_next;
	key_prev_func = disp_brightness_prev;
	key_enter_func = NULL;
	key_back_func = disp_brightness_back;

	disp_brightness_refresh();

}

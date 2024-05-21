/*
 * TIME.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */

//#include "main.h"
#include "MENU.h"
#include "i2c-lcd.h"
#include "RTC.h"
#include "TIME.h"
#include "LCD_BUF.h"

uint8_t time_call = 0;
char time[10];
char date[10];

extern void (*key_next_func)();
extern void (*key_prev_func)();
extern void (*key_enter_func)();
extern void (*key_back_func)();

void time_callback() {

	key_next_func = NULL;
	key_prev_func = NULL;
	key_enter_func = get_time;
	key_back_func = time_back;
	time_refresh();
	time_call = 1;

}

void time_refresh() {

	buf_clear();
    buf_locate(0, 1);
    buf_str(time);
    buf_locate(1, 1);
    buf_str(date);

}

void time_back() {

	key_next_func = menu_next;
	key_prev_func = menu_prev;
	key_enter_func = menu_enter;
	key_back_func = menu_back;
	time_call = 0;
	menu_refresh();

}

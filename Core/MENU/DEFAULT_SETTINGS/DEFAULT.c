/*
 * DEFAULT.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */


/*
 * BRIGHTNESS.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */

#include "MENU.h"
#include "main.h"
#include "i2c-lcd.h"
#include "DEFAULT.h"
#include "LCD_BUF.h"
#include <string.h>
#include "LANGUAGE/LANGUAGE.h"

extern void (*key_next_func)();
extern void (*key_prev_func)();
extern void (*key_enter_func)();
extern void (*key_back_func)();
extern char lcd_buffer[LCD_ROWS][LCD_COLS];


extern menu_t *temp;
extern menu_t *currentPointer; // baslangicta ilk menuden baslar

void default_settings(){

	english_language();
	TIM4->CCR3 = 65000;
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	default_refresh();
}

void default_back(){

	key_next_func = menu_next;
	key_prev_func = menu_prev;
	key_enter_func = menu_enter;
	key_back_func = menu_back;

	menu_refresh();

}

void default_refresh(){

	buf_clear();
	buf_locate(0, 0);
	buf_str("Factory Set");


}

void default_callback(){

	key_next_func = NULL;
	key_prev_func = NULL;
	key_enter_func = NULL;
	key_back_func = default_back;
	default_settings();
	default_refresh();

}

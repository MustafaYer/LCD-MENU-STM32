/*
 * LED.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */
#include "main.h"
#include "MENU.h"
#include "i2c-lcd.h"
#include "LED/LED.h"
#include "LCD_BUF.h"

extern void (*key_next_func)();
extern void (*key_prev_func)();
extern void (*key_enter_func)();
extern void (*key_back_func)();
uint8_t pinState = 0;

void led_toggle() {

	// LED'in durumunu değiştir
	if (pinState == 1) {
		// LED açıksa kapat
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
	} else {
		// LED kapalıysa aç
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	}

	led_toggle_refresh();

}

void led_toggle_callback() {

	key_next_func = NULL;
	key_prev_func = NULL;
	key_enter_func = led_toggle;
	key_back_func = led_toggle_back;
	led_toggle_refresh();

}

void led_toggle_refresh() {

	buf_locate(0, 0);
	buf_str("                ");

	buf_locate(0, 3);
	buf_str("-- LED --");

	buf_locate(1, 0);
	buf_str("                ");

	pinState = HAL_GPIO_ReadPin(LED_GPIO_Port, LED_Pin);

	// Ekranı güncelle
	if (pinState == 0) {
		// LED Yandı
		buf_locate(1, 6);
		buf_str("ON");
	} else if (pinState == 1) {
		// LED Söndü
		buf_locate(1, 6);
		buf_str("OFF");
	}
}

void led_toggle_back() {

	key_next_func = menu_next;
	key_prev_func = menu_prev;
	key_enter_func = menu_enter;
	key_back_func = menu_back;

	menu_refresh();

}

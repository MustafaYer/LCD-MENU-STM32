/*
 * LANGUAGE.c
 *
 *  Created on: May 20, 2024
 *      Author: musta
 */
#include "LANGUAGE.h"
#include "MENU.h"
#include "main.h"
#include "i2c-lcd.h"
#include "LCD_BUF.h"

extern void (*key_next_func)();
extern void (*key_prev_func)();
extern void (*key_enter_func)();
extern void (*key_back_func)();

extern menu_t menu1;
	extern 	menu_t sub_menu1_1;
		extern 	menu_t sub_menu1_1_1;
		extern 	menu_t sub_menu1_2_1;
	extern 	menu_t sub_menu1_2;

extern 	menu_t menu2;
	extern 	menu_t sub_menu2_1;
	extern 	menu_t sub_menu2_2;
		extern menu_t sub_menu2_2_1;
		extern menu_t sub_menu2_2_2;

extern menu_t menu3;

extern menu_t menu4;

extern menu_t menu5;
	extern menu_t sub_menu5_1;
	extern menu_t sub_menu5_2;

extern menu_t menu6;

extern menu_t *currentPointer; // baslangicta ilk menuden baslar

void turkish_language() {

	menu1.name = "GOSTERGE";
		sub_menu1_1.name = "KONTRAST";
			sub_menu1_1_1.name = "TEST";
		sub_menu1_2.name = "PARLAKLIK";
			sub_menu1_2_1.name = "Seviye";

	menu2.name = "UART";
		sub_menu2_1.name = "BAUD HIZI";
		sub_menu2_2.name = "VERI BITLERI";
			sub_menu2_2_1.name = "DURDURMA BITI";
			sub_menu2_2_2.name = "Parity BITI";

	menu3.name = "LED YAKMA";
	menu4.name = "ZAMAN";
	menu5.name = "DIL";
		sub_menu5_1.name = "TURKCE";
		sub_menu5_2.name = "INGILIZCE";

		menu6.name = "FABRIKA AYARI";
}

void turkish_language_refresh() {

	buf_clear();
	buf_locate(1, 0);
	buf_str("DIL TURKCE OLDU");
}

void turkish_language_callback() {

	key_next_func = NULL;
	key_prev_func = NULL;
	key_enter_func = NULL;
	key_back_func = language_back;
	turkish_language();
	turkish_language_refresh();

}

void english_language() {

	menu1.name = "DISPLAY";
		sub_menu1_1.name = "CONTRAST";
			sub_menu1_1_1.name = "TEST";
		sub_menu1_2.name = "BRIGHTNESS";
			sub_menu1_2_1.name = "LEVEL";

	menu2.name = "UART";
		sub_menu2_1.name = "BAUDRATE";
		sub_menu2_2.name = "DATA BIT";
			sub_menu2_2_1.name = "STOP BIT";
			sub_menu2_2_2.name = "Parity BIT";

	menu3.name = "LED TOGGLE";
	menu4.name = "TIME";
	menu5.name = "LANGUAGE";
		sub_menu5_1.name = "TURKISH";
		sub_menu5_2.name = "ENGLISH";
	menu6.name = "DEFAULT SET";
}

void english_language_refresh() {

	buf_clear();
	buf_locate(1, 0);
	buf_str("LANG IS ENGLISH");
}

void english_language_callback() {

	key_next_func = NULL;
	key_prev_func = NULL;
	key_enter_func = NULL;
	key_back_func = language_back;
	english_language();
	english_language_refresh();

}

void language_back() {

	key_next_func = menu_next;
	key_prev_func = menu_prev;
	key_enter_func = menu_enter;
	key_back_func = menu_back;

	menu_refresh();

}

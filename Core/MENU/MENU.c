/*
 * Author: �ukasz �aguna
 * E-mail: kontakt@embeddedev.pl
 * Blog:   www.EmbeddedDev.pl
 *
 * LCD HD44780 MENU
 * Tutorial(in polish): http://www.embeddeddev.pl/menu-lcd-implementacja/
 *
 * MCU: STM32F103
 *
 */
//#include "main.h"
#include <string.h>

#include "i2c-lcd.h"
#include "MENU.h"
#include "LCD_BUF.h"
#include "main.h"
#include "ROTARY_ENCODER.h"
#include "RTC.h"
#include "BRIGTHNESS/BRIGHTNESS.h"
#include "TIME/TIME.h"
#include "LED/LED.h"
#include "LANGUAGE/LANGUAGE.h"
#include "DEFAULT_SETTINGS/DEFAULT.h"

menu_t menu1;
	menu_t sub_menu1_1;
	menu_t sub_menu1_1_1;
	menu_t sub_menu1_2_1;
		menu_t sub_menu1_1_brightness;
	menu_t sub_menu1_2;

	menu_t menu2;
		menu_t sub_menu2_1;
		menu_t sub_menu2_2;
			menu_t sub_menu2_2_1, sub_menu2_2_2;
menu_t menu3;
menu_t menu4;
menu_t menu5;
	menu_t sub_menu5_1;
	menu_t sub_menu5_2;
menu_t menu6;


// definition of menu's components: (*name, *next, *prev, *child, *parent, (*menu_function))
menu_t menu1 = { "DISPLAY", &menu2, &menu6, &sub_menu1_1, NULL, NULL };
	menu_t sub_menu1_1 = { "CONTRAST", &sub_menu1_2, &sub_menu1_2, &sub_menu1_1_1, &menu1, NULL };
		menu_t sub_menu1_1_1 = { "TEST", NULL, NULL, NULL, &sub_menu1_1, NULL };
	menu_t sub_menu1_2 = { "Brightness", &sub_menu1_1, &sub_menu1_1, NULL, &menu1, disp_brightness_callback };
		menu_t sub_menu1_2_1 = { "Seviye", NULL, NULL, NULL, &sub_menu1_2, NULL };

menu_t menu2 = { "UART", &menu3, &menu1, &sub_menu2_1, NULL, NULL };
	menu_t sub_menu2_1 = { "Baudrate", &sub_menu2_2, &sub_menu2_2, NULL, &menu2, NULL };
	menu_t sub_menu2_2 = { "Data Bits", &sub_menu2_1, &sub_menu2_1, &sub_menu2_2_1, &menu2, NULL };
		menu_t sub_menu2_2_1 = { "Stop Bit", &sub_menu2_2_2, &sub_menu2_2_2, NULL, &sub_menu2_2, NULL };
		menu_t sub_menu2_2_2 = { "Parity", &sub_menu2_2_1, &sub_menu2_2_1, NULL, &sub_menu2_2, NULL };

menu_t menu3 = { "LED TOGGLE", &menu4, &menu2, NULL, NULL, led_toggle_callback };
menu_t menu4 = { "TIME", &menu5, &menu3, NULL, NULL, time_callback };
menu_t menu5 = { "LANGUAGE", &menu6, &menu4, &sub_menu5_1, NULL, NULL };
	menu_t sub_menu5_1 = { "TURKISH", &sub_menu5_2, &sub_menu5_2, NULL, &menu5, turkish_language_callback };
	menu_t sub_menu5_2 = { "ENGLISH", &sub_menu5_1, &sub_menu5_1, NULL, &menu5, english_language_callback };

menu_t menu6 = { "DEFAULT SET", &menu1, &menu5, NULL, NULL, default_callback };

menu_t *currentPointer = &menu1; // baslangicta ilk menuden baslar

uint8_t menu_index = 0;
uint8_t lcd_row_pos = 0;
uint8_t lcd_row_pos_level_1, lcd_row_pos_level_2;

extern char lcd_buffer[LCD_ROWS][LCD_COLS];

extern uint8_t sag;
extern uint8_t sol;

extern char time[10];
extern char date[10];

extern uint8_t buton;
extern uint8_t back_button;
extern uint32_t currentTime;

void (*key_next_func)() = &menu_next;
void (*key_prev_func)() = &menu_prev;
void (*key_enter_func)() = &menu_enter;
void (*key_back_func)() = &menu_back;

menu_t *temp;

void menu_refresh() {

	uint8_t i;
	uint32_t center = 0;

    for (uint8_t y = 0; y < LCD_COLS ; y++) {
        lcd_buffer[0][y] = '-'; // 255 dolu karakteri temsil ediyor.
    }

	if (currentPointer->parent) {
		temp = (currentPointer->parent)->child;
		center = ( LCD_COLS - (strlen((temp->parent)->name)) )>>1;
		buf_locate(0,center-1);
		buf_char(' ');
		buf_str((temp->parent)->name);
		buf_char(' ');

	} else {
		center = (LCD_COLS - 4)>>1;
		temp = &menu1;
		buf_str_XY(0,center,"MENU");
	}

	for (i = 0; i != menu_index; i++) {
		temp = temp->next;
	}
		buf_locate(1, 0);
		if (temp == currentPointer){
			buf_char(62); // > karakteri
		}

		buf_locate(1, 1);
		buf_str(temp->name);
		uint8_t lenght = (strlen(temp->name));
		for(int i = lenght + 1; i < LCD_COLS;i++){
			lcd_buffer[1][i] = ' ';
		}

		temp = temp->next;
}

uint8_t menu_get_index(menu_t *q) {

	menu_t *temp;
	uint8_t i = 0;

	if (q->parent){
		temp = (q->parent)->child;
	}
	else{
		temp = &menu1;
	}

    while (temp != NULL && temp != q) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        return 0; // q menüde bulunamadıysa 0 döndür
    }
	return i;
}

uint8_t menu_get_level(menu_t *q) {

	menu_t *temp = q;
	uint8_t i = 0;

	if (!q->parent) return 0;

	while (temp->parent != NULL) {
		temp = temp->parent;
		i++;
	}

	return i;
}

void menu_next() { // sonraki ögeye git

	if (currentPointer->next) { // bir sonraki öge varsa

		currentPointer = (*currentPointer).next; //currentPointer işaretçisi, bir sonraki öğeyi işaret eder hale gelir
		menu_index++; // Bu değişken, mevcut menü öğesinin dizinini tutar
	} else { // bir sonraki öge yoksa
		menu_index = 0; // Bu, menüde ilk öğeye dönüşü ifade eder.
		lcd_row_pos = 0;

		if (currentPointer->parent){//bir üst menü öğesi varsa
			currentPointer = (currentPointer->parent)->child;
		} else{//üst menü öğesi yoksa
			currentPointer = &menu1;
		}
	}
	menu_refresh();
}

void menu_prev() { // önceki ögeye git
    if (currentPointer == NULL || currentPointer->prev == NULL) {
        return; // geçersiz pointer, hiçbir şey yapmadan çık
    }

	currentPointer = currentPointer->prev;

	if (menu_index) { //mevcut öğe menünün ilk öğesi değilse

		menu_index--;
		if (lcd_row_pos > 0)
			lcd_row_pos--;

	} else { //mevcut öğe menünün ilk öğesi ise

		menu_index = menu_get_index(currentPointer);

		if (menu_index >= LCD_ROWS - 1)
			lcd_row_pos = LCD_ROWS - 1;
		else
			lcd_row_pos = menu_index;
	}

	menu_refresh();
}

void menu_enter() {

	if (currentPointer->menu_function){
		currentPointer->menu_function();// menü öğesi bir fonksiyonu tetikliyorsa, bu fonksiyon burada çağrılır.
	}

	if (currentPointer->child)//mevcut menü öğesinin alt öğeleri varsa
	{
		switch (menu_get_level(currentPointer)) {
			case 0:
				lcd_row_pos_level_1 = lcd_row_pos;
				break;

			case 1:
				lcd_row_pos_level_2 = lcd_row_pos;
				break;
		}
		menu_index = 0;
		lcd_row_pos = 0;

		currentPointer = currentPointer->child;

		menu_refresh();
	}
}

void menu_back(void) {

	if (currentPointer->parent) {

		switch (menu_get_level(currentPointer)) {
			case 1:
				lcd_row_pos = lcd_row_pos_level_1;
				break;

			case 2:
				lcd_row_pos = lcd_row_pos_level_2;
				break;
			}

		currentPointer = currentPointer->parent;
		menu_index = menu_get_index(currentPointer);

		menu_refresh();
	}
}

void key_next_press(void) {

	if ( sag == 1) {

		sag = 0;

		if (key_next_func){
			(*key_next_func)();
		}

	} else if ( sol == 1){

		sol = 0;
		if (key_prev_func){
			(*key_prev_func)();
		}
	}

}

void key_enter_press(void){

	static uint8_t key_enter_lock = 0;

	if( !key_enter_lock && buton == 1 ) {

		key_enter_lock = 1;

		if(key_enter_func){
			(*key_enter_func)();
		}

	} else if(key_enter_lock && buton == 0 ){
		key_enter_lock++;
	}

}

void back_enter_press(){
	static uint8_t key_enter_lock = 0;

	if( !key_enter_lock && back_button == 1 ) {

		key_enter_lock = 1;

		if(key_back_func){
			(*key_back_func)();
		}

	} else if(key_enter_lock && back_button == 0 ){
		key_enter_lock++;
	}
}



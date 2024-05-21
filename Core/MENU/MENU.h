/*
 * MENU.h
 *
 *  Created on: May 10, 2024
 *      Author: musta
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

typedef struct menu_struct menu_t;

struct menu_struct {

	char * name;
	menu_t * next;
	menu_t * prev;
	menu_t * child;
	menu_t * parent;
	void (*menu_function)();

};

void menu_refresh();
void menu_next();
void menu_prev();
void menu_enter();
void menu_back();
void main_menu();


void key_next_press();
void key_enter_press();
void key_enter_press();
void back_enter_press();


#endif /* INC_MENU_H_ */

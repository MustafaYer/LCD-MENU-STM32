/*
 * ROTARY_ENCODER.c
 *
 *  Created on: May 18, 2024
 *      Author: musta
 */

#include "ROTARY_ENCODER.h"
#include "main.h"

#define WINDOW_SIZE 4 // Pencere boyutu
#define WINDOW_MASK (WINDOW_SIZE - 1)
#define MAX_COUNT 16384

int counter = 0;
int readings[WINDOW_SIZE] = {0}; // Okunan değerler dizisi
int currentIndex = 0; // Şu anki indeks
int sum = 0; // Toplam değer
int average = 0; // Ortalama değer

int prev_counter = 0;
uint8_t sag = 0;
uint8_t sol = 0;
uint8_t buton = 0;

uint16_t btn_ctr_ok = 0;
uint8_t back_button = 0;
uint16_t back_btn_ctr_ok = 0;


void read_rotary_encoder() {
    // Mevcut değeri oku
    int currentReading = (TIM1->CNT) >> 2;

    if (currentReading > (MAX_COUNT >> 2)) {
        currentReading -= MAX_COUNT;
    }
    // Pencere boyunca toplamdan eski değeri çıkar
    sum -= readings[currentIndex];

    // Yeni okunan değeri diziye ekle
    readings[currentIndex] = currentReading;

    // Yeni değeri toplamaya ekle
    sum += readings[currentIndex];

    // İndeksi güncelle, pencere boyutuna göre döngüsel yap
//    currentIndex = (currentIndex + 1) % WINDOW_SIZE;
    currentIndex = (currentIndex + 1) & WINDOW_MASK;

    // Ortalama değeri hesapla
    average = sum / WINDOW_SIZE;

    // Filtrelenmiş değeri counter değişkenine ata
    counter = average;

    if (counter > prev_counter) {
    	sag = 0;
    	sol = 1;
    	prev_counter = counter;
    } else if (counter < prev_counter){
    	sol = 0;
    	sag = 1;
    	prev_counter = counter;
    }
}

void Read_Encoder_Button() {

	if (HAL_GPIO_ReadPin(SWITCH_GPIO_Port, SWITCH_Pin) == 0) {
		if (btn_ctr_ok == 20) { //buton parazit engelle
			btn_ctr_ok = 21;
			buton = 1;
		} else if (btn_ctr_ok < 20) {
			btn_ctr_ok++;
		}
	} else {
		buton = 0;
		btn_ctr_ok = 0;

	}

	//Back Button Read
	if (HAL_GPIO_ReadPin(BACK_BUTTON_GPIO_Port, BACK_BUTTON_Pin) == 1) {
		if (back_btn_ctr_ok == 20) { //buton parazit engelle
			back_btn_ctr_ok = 21;
			back_button = 1;
		} else if (back_btn_ctr_ok < 20) {
			back_btn_ctr_ok++;
		}
	} else {
		back_button = 0;
		back_btn_ctr_ok = 0;

	}
}

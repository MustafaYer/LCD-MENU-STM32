/*
 * RTC.c
 *
 *  Created on: May 19, 2024
 *      Author: musta
 */

#include "main.h"
#include "RTC.h"
#include "stdio.h"

extern RTC_HandleTypeDef hrtc;
extern char time[10];
extern char date[10];


void get_time(void) {

	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	/* Display time Format: hh:mm:ss */
	sprintf((char*) time, "%02d:%02d:%02d", gTime.Hours, gTime.Minutes,gTime.Seconds);
	/* Display date Format: dd-mm-yy */
	sprintf((char*) date, "%02d-%02d-%2d", gDate.Date, gDate.Month,2000 + gDate.Year);
}



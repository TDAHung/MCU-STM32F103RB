/*
 * timer.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#include "timer.h"

int timer_flag[NUMS_OF_TIMER];
int timer_counter[NUMS_OF_TIMER];

void setTimer(int index, int duration){
	timer_counter[index] = duration / CYCLE;
	timer_flag[index] = 0;
}

void timerRun(int index){
	if(timer_counter[index] >= 0) {
		timer_counter[index]--;
		if(timer_counter[index] <= 0) timer_flag[index] = 1;
	}
}

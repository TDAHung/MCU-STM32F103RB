/*
 * timer.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#define CYCLE 10

#define NUMS_OF_TIMER 6

extern int timer_flag[NUMS_OF_TIMER];

void setTimer(int,int);
void timerRun(int);
#endif /* INC_TIMER_H_ */

/*
 * fsm_trafficlight.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_FSM_TRAFFICLIGHT_H_
#define INC_FSM_TRAFFICLIGHT_H_

#include "main.h"
#include "timer.h"

#define REDVERFLAG			0
#define YELLOWVERFLAG		1
#define GREENVERFLAG		2
#define REDHORFLAG			3
#define YELLOWHORFLAG		4
#define GREENHORFLAG		5
#define BLINK				6

enum flow{
	HOR,
	VER
};

enum StateLight{
	INIT,
	RED,
	YELLOW,
	GREEN
};

extern enum StateLight currentStateVER;
extern enum StateLight currentStateHOR;

void turnOnLight(enum StateLight, enum flow);
void turnOnPedes(void);
void blinkyPedes(void);
void clearPedes(void);
void blinkyLight(enum StateLight);
void clearTrafficLight(void);
void displayTraffic(int *);

#endif /* INC_FSM_TRAFFICLIGHT_H_ */

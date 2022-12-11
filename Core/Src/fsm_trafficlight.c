/*
 * fsm_trafficlight.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#include "fsm_trafficlight.h"

#define NUMS_PORT 4
#define SoundPort GPIOA
#define SoundPin D12_Pin

GPIO_TypeDef * LedPortVER[NUMS_PORT/2] = {
		D2_GPIO_Port,
		D3_GPIO_Port,
};

GPIO_TypeDef * LedPortHOR[NUMS_PORT/2] = {
		D4_GPIO_Port,
		D5_GPIO_Port
};

uint16_t LedPinVER[NUMS_PORT/2] = {
	D2_Pin,
	D3_Pin
};

uint16_t LedPinHOR[NUMS_PORT/2] = {
	D4_Pin,
	D5_Pin
};

GPIO_TypeDef * LedPortPedes[2] = {
		D6_GPIO_Port,
		D7_GPIO_Port
};

uint16_t LedPinPedes[2] = {
		D6_Pin,
		D7_Pin
};


enum StateLight currentStateVER = INIT;
enum StateLight currentStateHOR = INIT;
unsigned char blink = 0;


void clearLight(enum flow direction){
	switch(direction){
	case HOR:
		for(int i = 0 ; i < NUMS_PORT / 2; i++){
			HAL_GPIO_WritePin(LedPortHOR[i],LedPinHOR[i],0);
		}
		break;
	case VER:
		for(int i = 0 ; i < NUMS_PORT / 2; i++){
			HAL_GPIO_WritePin(LedPortVER[i],LedPinVER[i],0);
		}
		break;
	}
}

void clearTrafficLight(void){
	clearLight(HOR);
	clearLight(VER);
}

void clearPedes(void){
	HAL_GPIO_WritePin(LedPortPedes[0],LedPinPedes[0],0);
	HAL_GPIO_WritePin(LedPortPedes[1],LedPinPedes[1],0);
	HAL_GPIO_WritePin(SoundPort,SoundPin,0);
}

void turnOnPedes(void){
	HAL_GPIO_WritePin(LedPortPedes[0],LedPinPedes[0],0);
	HAL_GPIO_WritePin(LedPortPedes[1],LedPinPedes[1],1);
	HAL_GPIO_WritePin(SoundPort,SoundPin,1);
}

void turnOnLight(enum StateLight currentState, enum flow direction){
	switch(direction){
	case HOR:
		switch(currentState){
		case INIT: break;
		case RED:
			clearLight(HOR);
			HAL_GPIO_WritePin(LedPortHOR[0],LedPinHOR[0],1);
			HAL_GPIO_WritePin(LedPortHOR[1],LedPinHOR[1],0);
			break;
		case YELLOW:
			clearLight(HOR);
			HAL_GPIO_WritePin(LedPortHOR[0],LedPinHOR[0],1);
			HAL_GPIO_WritePin(LedPortHOR[1],LedPinHOR[1],1);
			break;
		case GREEN:
			clearLight(HOR);
			HAL_GPIO_WritePin(LedPortHOR[0],LedPinHOR[0],0);
			HAL_GPIO_WritePin(LedPortHOR[1],LedPinHOR[1],1);
			break;
		}
		break;
	case VER:
		switch(currentState){
		case INIT: break;
		case RED:
			clearLight(VER);
			HAL_GPIO_WritePin(LedPortVER[0],LedPinVER[0],1);
			HAL_GPIO_WritePin(LedPortVER[1],LedPinVER[1],0);
			break;
		case YELLOW:
			clearLight(VER);
			HAL_GPIO_WritePin(LedPortVER[0],LedPinVER[0],1);
			HAL_GPIO_WritePin(LedPortVER[1],LedPinVER[1],1);
			break;
		case GREEN:
			clearLight(VER);
			HAL_GPIO_WritePin(LedPortVER[0],LedPinVER[0],0);
			HAL_GPIO_WritePin(LedPortVER[1],LedPinVER[1],1);
			break;
		}
		break;
	}
}

void blinkyLight(enum StateLight currentState){
	if(timer_flag[BLINK]){
		if(blink){
			clearTrafficLight();
			blink = 0;
		}
		else{
			turnOnLight(currentState,VER);
			turnOnLight(currentState,HOR);
			blink = 1;
		}
		setTimer(BLINK,500);
	}
}

void displayTrafficLight(enum flow direction, int * trafficTime){
	switch(direction){
	case HOR:
		switch(currentStateHOR){
		case INIT:
			clearTrafficLight();
			currentStateHOR = RED;
			break;
		case RED:
			turnOnLight(RED,HOR);
			if(timer_flag[HOR]){
				currentStateHOR = GREEN;
				setTimer(HOR,trafficTime[GREENHORFLAG - 3]);
			}
			break;
		case YELLOW:
			turnOnLight(YELLOW,HOR);
			if(timer_flag[HOR]){
				currentStateHOR = RED;
				setTimer(HOR,trafficTime[REDHORFLAG - 3]);
			}

			break;
		case GREEN:
			turnOnLight(GREEN,HOR);
			if(timer_flag[HOR]){
				currentStateHOR = YELLOW;
				setTimer(HOR, trafficTime[YELLOWHORFLAG - 3]);
			}
			break;
		}
		break;
	case VER:
		switch(currentStateVER){
		case INIT:
			clearTrafficLight();
			currentStateVER = GREEN;
			break;
		case RED:
			turnOnLight(RED,VER);
			if(timer_flag[VER]){
				currentStateVER = GREEN;
				setTimer(VER,trafficTime[GREENVERFLAG]);
			}

			break;
		case YELLOW:
			turnOnLight(YELLOW,VER);
			if(timer_flag[VER]){
				currentStateVER = RED;
				setTimer(VER,trafficTime[REDVERFLAG]);

			}
			break;
		case GREEN:
			turnOnLight(GREEN,VER);
			if(timer_flag[VER]){
				setTimer(VER,trafficTime[YELLOWVERFLAG]);
				currentStateVER = YELLOW;
			}
			break;
		}
		break;
	}
}

void displayTraffic(int * timeTraffic){
	displayTrafficLight(VER, timeTraffic);
//	displayTrafficLight(HOR, timeTraffic);
}

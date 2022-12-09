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

}

void turnOnPedes(void){
	HAL_GPIO_WritePin(LedPortPedes[0],LedPinPedes[0],1);
	HAL_GPIO_WritePin(LedPortPedes[1],LedPinPedes[1],0);
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
			HAL_GPIO_WritePin(LedPortVER[0],LedPinVER[0],0);
			HAL_GPIO_WritePin(LedPortVER[1],LedPinVER[1],1);
			break;
		case YELLOW:
			clearLight(VER);
			HAL_GPIO_WritePin(LedPortVER[0],LedPinVER[0],0);
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
		setTimer(BLINK,200);
	}
}

void displayTrafficLight(enum flow direction, int * trafficTime){
	switch(direction){
	case HOR:
		switch(currentStateHOR){
		case INIT:
			setTimer(REDHORFLAG,trafficTime[REDHORFLAG - 3]);
			setTimer(YELLOWHORFLAG,trafficTime[YELLOWHORFLAG - 3]);
			setTimer(GREENHORFLAG, trafficTime[GREENHORFLAG - 3]);
			clearTrafficLight();
			currentStateHOR = RED;
			break;
		case RED:
			if(timer_flag[REDHORFLAG]){
				setTimer(REDHORFLAG,trafficTime[REDHORFLAG - 3]);
				turnOnLight(RED,HOR);
			}
			currentStateHOR = GREEN;
			break;
		case YELLOW:
			if(timer_flag[YELLOWHORFLAG]){
				setTimer(YELLOWHORFLAG,trafficTime[YELLOWHORFLAG - 3]);
				turnOnLight(YELLOW,HOR);
			}
			currentStateHOR = RED;
			break;
		case GREEN:
			if(timer_flag[GREENHORFLAG]){
				setTimer(GREENHORFLAG, trafficTime[GREENHORFLAG - 3]);
				turnOnLight(GREEN,HOR);
			}
			currentStateHOR = YELLOW;
			break;
		}
		break;
	case VER:
		switch(currentStateVER){
		case INIT:
			clearTrafficLight();
			setTimer(REDVERFLAG,trafficTime[REDVERFLAG]);
			setTimer(GREENVERFLAG, trafficTime[GREENVERFLAG]);
			setTimer(YELLOWVERFLAG,trafficTime[YELLOWVERFLAG]);
			currentStateVER = GREEN;
			break;
		case RED:
			if(timer_flag[REDVERFLAG]){
				setTimer(REDVERFLAG,trafficTime[REDVERFLAG]);
				turnOnLight(RED,VER);
			}
			currentStateVER = GREEN;
			break;
		case YELLOW:
			if(timer_flag[YELLOWVERFLAG]){
				setTimer(YELLOWVERFLAG,trafficTime[YELLOWVERFLAG]);
				turnOnLight(YELLOW,VER);
			}
			currentStateVER = RED;
			break;
		case GREEN:
			if(timer_flag[GREENVERFLAG]){
				setTimer(GREENVERFLAG,trafficTime[GREENVERFLAG]);
				turnOnLight(GREEN,VER);
				currentStateVER = YELLOW;
			}
			break;
		}
		break;
	}
}

void displayTraffic(int * timeTraffic){
	displayTrafficLight(VER, timeTraffic);
	displayTrafficLight(HOR, timeTraffic);
}

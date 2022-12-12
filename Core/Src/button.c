/*
 * button.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#include "button.h"
#include "timer.h"

#define NUMS_OF_BUTTON 	4

#define BUTTON_HOLD 	1000
#define PRESSED 		GPIO_PIN_RESET
#define NORMAL			GPIO_PIN_SET

GPIO_TypeDef * buttonPort[NUMS_OF_BUTTON] = {
		button_mode_GPIO_Port,
		button_inc_GPIO_Port,
		button_dec_GPIO_Port,
		PedesButton_GPIO_Port
};

uint16_t buttonPin[NUMS_OF_BUTTON] = {
	button_mode_Pin,
	button_inc_Pin,
	button_dec_Pin,
	PedesButton_Pin
};

uint8_t buttonBuffer[NUMS_OF_BUTTON] = {NORMAL, NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer0[NUMS_OF_BUTTON] = {NORMAL, NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer1[NUMS_OF_BUTTON] = {NORMAL, NORMAL, NORMAL, NORMAL};
uint8_t ButtonBuffer2[NUMS_OF_BUTTON] = {NORMAL, NORMAL, NORMAL, NORMAL};

int flagButtonPressed[NUMS_OF_BUTTON];
int flagButtonHold[NUMS_OF_BUTTON];

int counterButtonHold[NUMS_OF_BUTTON] = {0, 0, 0, 0};

void buttonReading(){
	for(int i = 0; i < NUMS_OF_BUTTON; i++) {
		ButtonBuffer2[i] = ButtonBuffer1[i];
		ButtonBuffer1[i] = ButtonBuffer0[i];
		ButtonBuffer0[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);
		if((ButtonBuffer2[i] == ButtonBuffer1[i]) && (ButtonBuffer1[i] == ButtonBuffer0[i])) {
			if(buttonBuffer[i] != ButtonBuffer0[i]) {
				buttonBuffer[i] = ButtonBuffer0[i];
				if(buttonBuffer[i] == PRESSED) {
					counterButtonHold[i] = BUTTON_HOLD;
					if(CYCLE > 0) counterButtonHold[i] /= CYCLE;
					flagButtonPressed[i] = 1;
				}
				else flagButtonHold[i] = 0;
			}
			else {
				if(buttonBuffer[i] == PRESSED) {
					counterButtonHold[i]--;
					if(counterButtonHold[i] == 0) flagButtonHold[i] = 1;
				}
			}
		}
	}
}

int isButtonPressed(int index) {
	if(index < 0 || index > NUMS_OF_BUTTON) return 0;
	if(flagButtonPressed[index] == 1) {
		flagButtonPressed[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonHold(int index) {
	if(index < 0 || index > NUMS_OF_BUTTON) return 0;
	if(flagButtonHold[index] == 1) {
		return 1;
	}
	return 0;
}

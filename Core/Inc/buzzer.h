/*
 * buzzer.h
 *
 *  Created on: Dec 12, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

#define BZ_ON		81
#define BZ_OFF		82

extern uint8_t buzzer_state;

void buzzer_modify_volume(int volumeLevel); //modify volume of buzzer at volumeLevel
void buzzer_turn_on(); //turn on buzzer
void buzzer_turn_off(); //turn off buzzer or volume = 0

#endif /* INC_BUZZER_H_ */

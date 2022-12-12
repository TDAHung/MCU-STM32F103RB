/*
 * buzzer.c
 *
 *  Created on: Dec 12, 2022
 *      Author: Mr.HUNG
 */

#include "buzzer.h"

void buzzer_modify_volume(int volumeLevel) {
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, volumeLevel);
}

void buzzer_turn_on() {
	buzzer_modify_volume(50);
}

void buzzer_turn_off() {
	buzzer_modify_volume(0);
}

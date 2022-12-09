/*
 * uart_communication_fsm.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */
#include "uart_communication_fsm.h"

#define RESENDING_TIME 3000

enum uart_communication_fsm_state
{
	WAITING,
	CHECKING_COMMAND
};
enum uart_communication_fsm_state communication_state = WAITING;

char str[10];
char *led7seg = "7SEG:";

void uart_communiation_fsm(void)
{
	switch (communication_state)
	{
	case WAITING:
		if (command_flag)
			communication_state = CHECKING_COMMAND;
		break;
	case CHECKING_COMMAND:
		if (strstr(command_data, led7seg) != NULL)
		{
			char strnum7[10];
			int len7LED = strlen(led7seg);
			int lenCommand = strlen(command_data);
			strncpy(strnum7, command_data + len7LED, lenCommand - len7LED);
			strnum7[lenCommand - len7LED] = '\0';
			HAL_UART_Transmit(&huart2,(void *)str, printf("\r\n :%s\r\n",strnum7),1000);
		}
		else{
			HAL_UART_Transmit(&huart2,(void *)str, printf("\r\nInvalid Command\r\n"),1000);
		}
		communication_state = WAITING;
		command_data_size = 0;
		command_flag = 0;
		break;
	}
}

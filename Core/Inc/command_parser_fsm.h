/*
 * command_parser_fsm.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Mr.HUNG
 */

#ifndef INC_COMMAND_PARSER_FSM_H_
#define INC_COMMAND_PARSER_FSM_H_

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;

extern int command_flag;
extern char command_data[MAX_BUFFER_SIZE + 1];
extern int command_data_size;

void command_parser_fsm(void);


#endif /* INC_COMMAND_PARSER_FSM_H_ */

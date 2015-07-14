/*
 * state_manager.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mstagg
 */

#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

uint8_t state;
uint8_t data;
uint8_t len;
uint8_t msg[256];
uint8_t msgIndex;

void init_state_machine(void);
void manage_state(uint8_t data);

#endif /* STATE_MANAGER_H_ */

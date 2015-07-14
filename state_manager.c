/*
 * state_manager.c
 *
 *  Created on: Jul 14, 2015
 *      Author: mstagg
 */

#include <inttypes.h>
#include "state_manager.h"

void init_state_machine(void){
	msgIndex = 0;
	state = 0;
}

void manage_state(uint8_t data){
	// Each legitimate advertisement packet has prefix {0x80, MSG_SIZE, 0x06, 0x00}
		// Prefix is followed by data payload of size MSG_SIZE to complete advertisement packet
		switch(state){
			case 0:
				state = (data == 0x80) ? 1 : 0;
				break;
			case 1:
				len = data;
				state = 2;
				break;
			case 2:
				state = (data == 0x06) ? 3 : 0;
				break;
			case 3:
				state = (data == 0x00) ? 4 : 0;
				break;
			case 4:
				if(len > 0){
					msg[msgIndex] = data;
					msgIndex++;
					len--;
				} else{
					state = 5;
				}
				break;
		}
}


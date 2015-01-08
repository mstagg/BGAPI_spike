/*
 * wan.h
 *
 *  Created on: Nov 5, 2014
 *      Author: titan
 */

#ifndef WAN_H_
#define WAN_H_

#include "wan_msg.h"
//#include "../queue/queue.h"
// btle parsing results
enum wan_parse_result {
 WAN_TKNOTFOUND = 0,
 WAN_TKFOUND,
 WAN_TKERROR,
 WAN_TKTIMEOUT
};

// token start and end
#define WAN_TKSTART	'*'
#define WAN_TKEND		'\n'
#define WAN_MSG_QUEUE_SIZE			MSG_SIZE * 128



void wan_init();
void wan_tick();
void wan_set_cts();//pd5 output and low
uint8_t wan_get_rts();//pd4 input

#endif /* WAN_H_ */

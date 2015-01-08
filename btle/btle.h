/*
 * btle.h
 *
 *  Created on: Nov 3, 2014
 *      Author: jcobb
 */

#ifndef BTLE_H_
#define BTLE_H_

#include "btle_msg.h"

// btle parsing results
enum btle_parse_result {
 BTLE_TKNOTFOUND = 0,
 BTLE_TKFOUND,
 BTLE_TKERROR,
 BTLE_TKTIMEOUT
};

// token start and end
#define BTLE_TKSTART	"*"
#define BTLE_TKEND		"\n"
#define MSG_QUEUE_SIZE			MSG_SIZE * 128


void btle_init();
void btle_tick();
uint8_t btle_get_rts();//pd4 input
uint8_t btle_get_cts();//pd5 input



#endif /* BTLE_H_ */

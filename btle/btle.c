/*
 * btle.c
 *
 *  Created on: Nov 3, 2014
 *      Author: jcobb
 */

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "../usart/usart_btle.h"
#include "btle.h"
#include "btle_msg.h"
#include "btle_driver.h"
#include "../usart/usart_wan.h"

uint8_t start_up_msg[5] = {0x00, 0x01, 0x06, 0x02, 0x01};

void btle_init()
{
	//btle_usart_init();
	// set portd bit 5 as output
	DDRD |= _BV(PD5);
	// set portd bit 4 as input
	DDRD &= ~_BV(PD4);

	btle_set_cts('L');
	btle_driver_init();
	btle_usart_transmit_bytes(start_up_msg, 5);
	btle_set_cts('H');
	btle_usart_clear_buffer();


}


uint8_t btle_get_cts()
{
	// return logic high or low
	return (PIND & _BV(PD5));
}


uint8_t btle_get_rts()
{
	// return logic high or low
	return (PIND & _BV(PD4));
}



void btle_tick()
{
	btle_driver_tick();
}




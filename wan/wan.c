/*
 * wan.c
 *
 *  Created on: Nov 5, 2014
 *      Author: titan
 */


#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "../usart/usart_wan.h"
#include "wan.h"
#include "wan_msg.h"
#include "wan_driver.h"


void wan_init()
{
	wan_usart_init();
	//wan_usart_get_device_address();

	wan_driver_init();
}

void wan_set_cts()
{
	//pd0 low
	PORTD &= ~_BV(PD0);
}

uint8_t wan_get_rts()
{
	// return logic high or low
	return (PIND & _BV(PD1));
}


void wan_tick()
{
	wan_driver_tick();

}


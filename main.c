/*


 * main.c
 *
 *  Created on: Nov 3, 2014
 *      Author: jcobb
 */

#define F_CPU		8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btle/btle.h"
#include "usart/usart_btle.h"
#include "usart/usart_wan.h"
#include "wan/wan_driver.h"
#include "wan/wan.h"

volatile char term_in = 0;

void terminal_in_cb(uint8_t c)
{
	term_in = c;

}

void main()
{
	// Blinky test!
	DDRD |= _BV(PD6); // data direction bit
	DDRD |= _BV(PD7);

	DDRB &= _BV(PB0); // WAN_INT_01

	//debug_init(terminal_in_cb);
	btle_usart_init_cb(terminal_in_cb);


	// btle is on usart1
	btle_init();

	// wan is on usart0
	wan_init();


	sei();

	while(true)
	{

		btle_tick();
		wan_tick();

		term_in = 0;

	}
}









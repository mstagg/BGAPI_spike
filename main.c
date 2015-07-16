/*


 * main.c
 *
 *  Created on: July 13th, 2015
 *      Author: Matthew Stagg
 */

#define F_CPU 8000000
#define PRINT_BUFFER_SIZE 256

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart/usart_btle.h"
#include "usart/usart_wan.h"
#include "wan/wan_driver.h"
#include "wan/wan.h"
#include "parser/packet_parser.h"
#include "bgapi/bg_api.h"



void init(void){
		// set portD bit 5 (flow control) as output
		DDRD |= _BV(PD5);

		// Initial setup
		btle_usart_init();
		wan_usart_init();
		bg_api_discover_init();
		init_state_machine();

		// Init Events...
		sei();

		// Open flow control
		PORTD &= ~_BV(PD5);
}

int main(void)
{
	char c[PRINT_BUFFER_SIZE];

	init();

	for(;;)
	{

		// State and PACKAGE defined in parser/packet_parser
		if (state == 5) {
			// Close flow control
			PORTD |= _BV(PD5);

			PACKAGE *pkg = parse(msg);

			get_address_string(pkg, c);
			wan_usart_transmit_string("Address: ");
			wan_usart_transmit_string(c);
			wan_usart_transmit_string("\r\n");

			get_data_length_string(pkg, c);
			wan_usart_transmit_string("Data Length: ");
			wan_usart_transmit_string(c);
			wan_usart_transmit_string("\r\n");

			get_data_string(pkg, c);
			wan_usart_transmit_string("Data: ");
			wan_usart_transmit_string(c);
			wan_usart_transmit_string("\r\n\n");

			//To transmit raw hex data of entire message... uncomment
			//wan_usart_transmit_bytes(msg, msgIndex);

			msgIndex = 0;
			state = 0;
			free(pkg);

			//Open flow control
			PORTD &= ~_BV(PD5);
		}
	}
	return 0;
}

// Event: Received byte over bluetooth UART
// Manages state machine
ISR(USART1_RX_vect){
	data = UDR1;
	manage_state(data);
}








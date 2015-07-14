/*


 * main.c
 *
 *  Created on: July 13th, 2015
 *      Author: Matthew Stagg
 */

#define F_CPU		8000000
#define PRINT_BUFFER_SIZE 256

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "usart/usart_btle.h"
#include "usart/usart_wan.h"
#include "wan/wan_driver.h"
#include "wan/wan.h"
#include "packet_parser.h"
#include "state_manager.h"

int main()
{
	// Init Events...
	sei();

	// set portD bit 5 (flow control) as output
	DDRD |= _BV(PD5);

	// Initial setup
	init_state_machine();
	btle_usart_init();
	wan_usart_init();
	// Open flow control
	PORTD &= ~_BV(PD5);

	// BGAPI commands
	// Can be found in bluetooth smart software reference PDF on pg. 101, 102, and 111. respectively
	uint8_t discoverCmd[] = {0x00, 0x01, 0x06, 0x02, 0x01};
	uint8_t endDiscoverCmd[] = {0x00, 0x00, 0x06, 0x04};
	uint8_t discoverParams[] = {0x00, 0x05, 0x06, 0x07, 0x40, 0x00, 0x32, 0x00, 0x00};

	// BGAPI initialization commands
	btle_usart_clear_buffer();
	btle_usart_transmit_bytes(endDiscoverCmd, 4);
	_delay_ms(100);
	btle_usart_transmit_bytes(discoverParams, 9);
	_delay_ms(100);
	btle_usart_transmit_bytes(discoverCmd, 5);

	char c[PRINT_BUFFER_SIZE];
	while(true)
	{
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









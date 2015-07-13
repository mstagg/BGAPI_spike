/*


 * main.c
 *
 *  Created on: July 13th, 2015
 *      Author: Matthew Stagg
 */

#define F_CPU		8000000

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

uint8_t state = 0;
volatile unsigned char data;
volatile unsigned char len;
volatile unsigned char msg[256];
volatile unsigned char msgIndex = 0;

void main()
{
	// Init Events...
	sei();

	// set portD bit 5 (flow control) as output
	DDRD |= _BV(PD5);

	// USART setup
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

	while(true)
	{
		if (state == 5) {
			// Close flow control
			PORTD |= _BV(PD5);

			// Store into string and transmit MAC address of advertiser
			char *c = malloc(sizeof(*c));
			sprintf(c, "MSG FROM: %02x:%02x:%02x:%02x:%02x:%02x -> ", msg[2], msg[3], msg[4], msg[5], msg[6], msg[7]);
			wan_usart_transmit_string(c);

			// Store into string and transmit data payload
			int i;
			for(i = 10; i < msgIndex; i++){
				sprintf(c, "%02X ", msg[i]);
				wan_usart_transmit_string(c);
			}
			wan_usart_transmit_string("\r\n\n");

			//To transmit raw hex data of entire message... uncomment
			//wan_usart_transmit_bytes(msg, msgIndex);

			msgIndex = 0;
			state = 0;
			free(c);

			//Open flow control
			PORTD &= ~_BV(PD5);
		}
	}
}

// Event: Received byte over bluetooth UART
// Manages state machine
ISR(USART1_RX_vect){
	data = UDR1;

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









/*
 * bg_api.c
 *
 *  Created on: Jul 14, 2015
 *      Author: mstagg
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include "../usart/usart_btle.h"
#include "../usart/usart_wan.h"
#include "../wan/wan_driver.h"
#include "../wan/wan.h"

#define RESPONSE_SIZE 6

// BGAPI commands
// Can be found in bluetooth smart software reference PDF on pg. 101, 102, and 111. respectively
uint8_t discoverCmd[] = {0x00, 0x01, 0x06, 0x02, 0x01};
uint8_t endDiscoverCmd[] = {0x00, 0x00, 0x06, 0x04};
uint8_t discoverParams[] = {0x00, 0x05, 0x06, 0x07, 0x40, 0x00, 0x32, 0x00, 0x00};

// Check for properly formatted discovery response from BG chip
uint8_t discover_response_listen(void){
	uint8_t checkState = 0;
	uint8_t data;

	int i;
	// Only check first 20 bytes across the UART line
	for(i = 0; i < 20; i++){
		while ( !(UCSR1A & (1<<RXC1)) );
		data = UDR1;
		switch(checkState){
			case 0:
				checkState = (data == 0x00) ? 1 : 0;
				break;
			case 1:
				checkState = (data == 0x02) ? 2 : (data == 0x00) ? 1 : 0;
				break;
			case 2:
				checkState = (data == 0x06) ? 3 : 0;
				break;
			case 3:
				checkState = (data == 0x02) ? 4 : 0;
				break;
			case 4:
				checkState = (data == 0x00) ? 5 : 0;
				break;
			case 5:
				if(data == 0x00){
					return 1;
				} else{
					checkState = 0;
				}
				break;
		}
	}
	return 0;
}

void bg_api_discover_init(void){
	cli();

	// End any running discovery mode and start a new one
	btle_usart_transmit_bytes(endDiscoverCmd, 4);
	_delay_ms(500);
	btle_usart_transmit_bytes(discoverParams, 9);
	_delay_ms(500);
	btle_usart_transmit_bytes(discoverCmd, 5);

	// Continue to end discovery mode and restart it until an error free response code is received
	while(!(discover_response_listen())){
		btle_usart_transmit_bytes(endDiscoverCmd, 4);
		_delay_ms(500);
		btle_usart_transmit_bytes(discoverParams, 9);
		_delay_ms(500);
		btle_usart_transmit_bytes(discoverCmd, 5);
	}

	sei();
}

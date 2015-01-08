/*
 * btle_driver.c

 *
 *  Created on: Nov 4, 2014
 *      Author: jcobb
 */

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "../usart/usart_btle.h"
#include "btle_driver.h"
#include "btle.h"
#include "btle_msg.h"
#include "../usart/usart_wan.h"

char HEX_DIGITS[] = "0123456789abcdef";

#define BTLE_MAX_CHARS		128
#define DEBUG_OUTPUT "rssi=%d batt=%d temp=%d mac=%d \r\n\0"

uint8_t btle_lines[BTLE_MAX_CHARS + 1];
uint8_t header_buffer[14];
int btle_index = 0;
uint8_t new_line = 0;
int line_ready = 1;
int msg_length = 1;
int msg_index = 0;


uint8_t btle_line_buffer[BTLE_MAX_CHARS + 1];
int btle_line_index = 0;

void encode_string(btle_msg_t * value);
static void init_buffer();
static void init_lines();
static bool handle_data();

void btle_driver_init() {
	init_buffer();
	init_lines();
	btle_usart_clear_buffer();
}

void btle_set_cts(char mode)
{
	//pd5 low
	if(mode == 'L')
		PORTD &= ~_BV(PD5);

	//pd5 high
	else if(mode == 'H')
		PORTD |= _BV(PD5);
}

void btle_driver_tick() {

	if(line_ready)
		btle_set_cts('L');



	if (btle_usart_data_available())
	{
		if (handle_data())
		{
			line_ready = 0;
			btle_set_cts('H');

			if(validate_line())
			{
				wan_usart_transmit_string("TICK\r\n");
/*
				btle_msg_t msg;
				msg.rssi = btle_lines[4];
				msg.mac = 0;
				msg.batt = 0;
				msg.temp = 0;

				//mac adress is stored in array bytes 6-11
				uint8_t mac_address[6];
				memcpy(mac_address, &btle_lines[6], 6*sizeof(uint8_t));


				//convert the array to one value + 2 bytes of garbage
				msg.mac = *(uint64_t *)mac_address;
				msg.mac <<= 16; // shift out the garbage bytes, get zero's in.
				msg.mac >>= 16; // and shift back again.



				msg.batt = 200;
				msg.temp = 200;

				if (msg.mac != 0)
					{

						if (!(PINB & (1 << PB0)))
							{
								encode_string(&msg);
							}

					}
*/
					init_lines();
			}

		}
	}
}

bool validate_line()
{
	if(btle_lines[2] == 0x06 && btle_lines[0] == 0x80)
	{
		//wan_usart_transmit_string("Passed tests!\r\n");
		line_ready = 1;
		btle_usart_clear_buffer();
		return true;
	}



	line_ready = 1;
	init_lines();
	btle_usart_clear_buffer();

	return false;
}

void encode_string(btle_msg_t * value) {
	char tmp[50];

	memset(tmp, '\0', 50);
	sprintf_P(tmp, PSTR(DEBUG_OUTPUT), value->rssi, value->batt, value->temp, value->mac);
	wan_usart_transmit_string(tmp);
}

void print_bytes()
{
	uint8_t x;
	int temp_size = 14 + msg_length;
	char temp[3*(temp_size)];
	int temp_index = 0;

	for (int i=0;i<temp_size;i++)
	{
		x = (uint8_t)HEX_DIGITS[(btle_lines[i] >> 4)];
		temp[temp_index] = x;
		temp_index++;
		x = (uint8_t)HEX_DIGITS[(btle_lines[i] & 0x0f)];
		temp[temp_index] = x;
		temp_index++;
		temp[temp_index] = ' ';
		temp_index++;

	}

	wan_usart_transmit_string(temp);
	wan_usart_transmit_string("\r\n");
}

static void init_buffer() {
	btle_line_index = 0;
	memset(btle_line_buffer, '\0', sizeof(btle_line_buffer));
}

static void init_lines() {
	memset(btle_lines, '\0', sizeof(btle_lines));
}

// check to see if we have a new line
bool handle_data()
{

	uint8_t c = btle_usart_data_read();


	// prevent buffer overrun
	if (btle_line_index >= 50)
	{
		init_buffer();
		btle_usart_clear_buffer();
		msg_index = 0;
		msg_index = 1;
		return false;
	}

	// store character in btle_line_buffer
	btle_line_buffer[btle_line_index] = c;

	//check for length
	if(btle_line_index == 14)
		msg_length = c;

	//check for payload
	if(btle_line_index > 14)
		msg_index++;

	//check for end of payload
	if(msg_index == msg_length)
	{
		memcpy(btle_lines, btle_line_buffer, btle_line_index);
		//print_bytes();
		init_buffer();
		msg_index = 0;
		msg_length = 1;
		return true;
	}


	btle_line_index++;

	return false;
}


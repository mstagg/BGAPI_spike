/*
 * wan_driver.c
 *
 *  Created on: Nov 5, 2014
 *      Author: titan
 */

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "../usart/usart_wan.h"
#include "../usart/usart_btle.h"
#include "wan_driver.h"
#include "wan.h"
#include "wan_msg.h"

char WAN_HEX_DIGITS[] = "0123456789abcdef";

#define WAN_MAX_CHARS		128

char wan_lines[WAN_MAX_CHARS + 1];
int wan_index = 0;
uint8_t wan_new_line = 0;

char wan_line_buffer[WAN_MAX_CHARS + 1];
int wan_line_index = 0;

static void init_buffer();
static void init_lines();
static bool handle_data();
static uint8_t parse_data(char *token, char **out);

static uint8_t wan_parse_nybble(char c);
static wan_msg_t wan_handle_packet(char * buffer);

char bytes_received[64];
char bytes_message[64];
uint8_t array_index = 0;
uint8_t message_index = 0;
int message_length = 0;
int cmd = 0;


void wan_driver_init()
{
	//queue_init(&wan_queue, WAN_MSG_QUEUE_SIZE);
	init_buffer();
	init_lines();
}

void wan_driver_tick()
{
	char temp_buff[80];
	if (wan_usart_data_available())
	{
		//btle_usart_transmit_string("here2\r\n");
		//btle_usart_transmit_string("here1\r\n");
		// get the bytes
		bytes_received[array_index] = wan_usart_data_read();
		if (array_index < 2)
		{
			bytes_message[message_index] = bytes_received[array_index];
		}
		// get the length
		if (array_index == 0)
		{
			message_length = bytes_received[array_index];
			sprintf(temp_buff, "len: %d", message_length);
			btle_usart_transmit_string(temp_buff);

		} else if (array_index == 1)
		{
			cmd = bytes_received[array_index];

		} else if (array_index == (message_length - 1)) // the end
		{
			// Good message, check command
			switch (cmd)
			{
			case 4:
				// we got device address
				//appConfig.wan_device_address = bytes_message;

				PORTD ^= _BV(PD7);
				break;
			}
			array_index = 0;
			message_index = 0;
		}
		array_index++;
		message_index++;
	}
}

static void init_buffer()
{
	wan_line_index = 0;
	memset(wan_line_buffer, '\0', sizeof(wan_line_buffer));
}

static void init_lines()
{
	memset(wan_lines, '\0', sizeof(wan_lines));
}

bool handle_data()
{

	char c = wan_usart_data_read();

	// ignore null terminated strings
	if (c == '\0')
		return false;
	// prevent buffer overrun
	if (wan_line_index >= WAN_MAX_CHARS)
		return false;

	// store character in btle_line_buffer
	wan_line_buffer[wan_line_index] = c;
	wan_line_index++;

	// check for end of line
	if (c == WAN_TKEND)
	{
		// copy new message into buffer
		strcpy(wan_lines, wan_line_buffer);
		init_buffer();
		return true;
	}

	return false;
}

static uint8_t parse_data(char *token, char **out)
{
	uint8_t *ptr = NULL;
	// TODO: review warning
	if ((ptr == strstr(wan_lines, token)))
	{
		if (out != NULL )
			*out = ptr;
		return WAN_TKFOUND;
	} else
		return WAN_TKNOTFOUND;
}

wan_msg_t wan_handle_packet(char * buffer)
{
	wan_msg_t wan_msg;

	return wan_msg;

}

uint8_t wan_parse_nybble(char c)
{
	if (c >= 'A' && c <= 'F')
		c = c | 0x20;
	for (uint8_t i = 0; i < 16; i++)
	{
		if (WAN_HEX_DIGITS[i] == c)
			return i;
	}
	return 0x80;
}

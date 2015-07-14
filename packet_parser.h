/*
 * packet_parser.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mstagg
 */

#ifndef PACKET_PARSER_H_
#define PACKET_PARSER_H_

#include <inttypes.h>

typedef struct pkg{
	char rssi;
	uint8_t packetType;
	uint8_t address[6];
	uint8_t addressType;
	uint8_t bond;
	uint8_t dataLen;
	uint8_t data[256];

} PACKAGE;

PACKAGE* parse(uint8_t msg[]);
void get_data_string(PACKAGE* pkg, char* strOut);
void get_data_length_string(PACKAGE* pkg, char* strOut);
void get_address_string(PACKAGE* pkg, char* strOut);
void get_address_type_string(PACKAGE* pkg, char* strOut);
void get_packet_type_string(PACKAGE* pkg, char* strOut);
void get_rssi_string(PACKAGE* pkg, char* strOut);
void get_bond_string(PACKAGE* pkg, char* strOut);


#endif /* PACKET_PARSER_H_ */

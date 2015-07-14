/*
 * packet_parser.c
 *
 *  Created on: Jul 14, 2015
 *      Author: mstagg
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "packet_parser.h"

#define RSSI_INDEX 			0
#define PACKET_TYPE_INDEX 	1
#define ADDRESS_INDEX 		2
#define ADDRESS_TYPE_INDEX 	8
#define BOND_INDEX 			9
#define DATA_LENGTH_INDEX 	10
#define DATA_INDEX 			11

PACKAGE* parse(uint8_t msg[]){
	PACKAGE* pkg = malloc(sizeof(PACKAGE));

	int i;
	pkg->rssi = msg[RSSI_INDEX];
	pkg->packetType = msg[PACKET_TYPE_INDEX];
	for(i = ADDRESS_INDEX; i < ADDRESS_TYPE_INDEX; i++){
		pkg->address[i - ADDRESS_INDEX] = msg[i];
	}
	pkg->addressType = msg[ADDRESS_TYPE_INDEX];
	pkg->bond = msg[BOND_INDEX];
	pkg->dataLen = msg[DATA_LENGTH_INDEX];
	for(i = 0; i < pkg->dataLen; i++){
		pkg->data[i] = msg[i + DATA_INDEX];
	}

	return pkg;
}

void get_data_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	char d[5];
	int i;
	for(i = 0; i < pkg->dataLen; i++){
		sprintf(d, "%02x ", pkg->data[i]);
		strcat(c, d);
	}
	strcpy(strOut, c);
	free(c);
}

void get_data_length_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x", pkg->dataLen);
	strcpy(strOut, c);
	free(c);
}

void get_address_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x:%02x:%02x:%02x:%02x:%02x", pkg->address[0], pkg->address[1], pkg->address[2], pkg->address[3], pkg->address[4], pkg->address[5]);
	strcpy(strOut, c);
	free(c);
}

void get_address_type_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x", pkg->addressType);
	strcpy(strOut, c);
	free(c);
}

void get_packet_type_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x", pkg->packetType);
	strcpy(strOut, c);
	free(c);
}

void get_rssi_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x", pkg->rssi);
	strcpy(strOut, c);
	free(c);
}

void get_bond_string(PACKAGE* pkg, char* strOut){
	memset(strOut, 0, sizeof(strOut)/ sizeof(strOut[0]));
	char* c = malloc(sizeof(*c));
	sprintf(c, "%02x", pkg->bond);
	strcpy(strOut, c);
	free(c);
}




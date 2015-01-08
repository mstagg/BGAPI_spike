/*
 * btle_driver.h
 *
 *  Created on: Nov 4, 2014
 *      Author: jcobb
 */

#ifndef BTLE_DRIVER_H_
#define BTLE_DRIVER_H_

void btle_driver_init();
void btle_driver_tick();
void btle_set_cts(char mode);//pd5 output and low
bool validate_line();
void print_bytes();


#endif /* BTLE_DRIVER_H_ */

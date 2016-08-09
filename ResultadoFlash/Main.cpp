/*
 * main.h
 *
 *  Created on: 19/07/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "mbed.h"
#include "../Logger/Logger.h"
#include "../FaultInjector/FaultInjector.h"
#include <iostream>

DigitalOut led4(LED4);

void reset() {
	DigitalOut desl(p6);
	led4 = 1;
	desl = 0;
	wait_ms(500);
	desl = 1;
	led4 = 0;
}

//extern "C" void mbed_reset();

int main() {
	FaultInjector f;
	//unsigned long ini = (unsigned long) 0x00040000;
	//unsigned long fim = 0x00080000 - 1;

	f.startInjectFault();

	//mbed_reset();

	return 0;
}

#endif /* MAIN_CPP_ */

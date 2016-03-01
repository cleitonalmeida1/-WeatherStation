/*
 * FaultInjector.h
 *
 *  Created on: 01/03/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef FAULTINJECTOR_FAULTINJECTOR_H_
#define FAULTINJECTOR_FAULTINJECTOR_H_

#include  "mbed.h"

class FaultInjector {
public:

	/*
	 * Identificar o modelo mbed
	 */

	FaultInjector();

	/*
	 * Tipos de falhas
	 * - Travamento do sistema
	 * - loop infinito
	 * - bit flip
	 */

	typedef enum {
		SYSTEM_CRASH, INFINITY_LOOP, BIT_FLIPING
	} FaultType;

	void crash(long t = 0);

	void infinityLoop(long t = 0);

	void inject(long t = 0);

	virtual ~FaultInjector();
};

#endif /* FAULTINJECTOR_FAULTINJECTOR_H_ */

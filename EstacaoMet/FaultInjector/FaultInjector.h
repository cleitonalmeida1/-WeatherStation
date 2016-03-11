/*
 ' * FaultInjector.h
 *
 *  Created on: 01/03/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef FAULTINJECTOR_FAULTINJECTOR_H_
#define FAULTINJECTOR_FAULTINJECTOR_H_

#include  "mbed.h"
#include "MemoryMap/MemoryMap64.h"
#include "MemoryMap/MemoryMap66_65.h"
#include "MemoryMap/MemoryMap66_65.h"
#include "MemoryMap/MemoryMap68.h"

class FaultInjector {
public:


	static const int DEFAULT_CHANGED_BYTES = 32; // Number of bytes changed in each fault injection.
	static const int DEFAULT_CHANGED_BITS = 0; // Number of bits changed in each byte: [0 <= n <= 8] (0 = random).

	typedef enum {
		SYSTEM_CRASH, INFINITY_LOOP, BIT_FLIPING
	} FaultType;

	typedef enum {
		USER = 0, FLASH, PERIPHERALS, DEFAULT
	} MemoryType;

	typedef enum {
		MBED_UNDEFINED = 0,
		MBED_LPC1764 = 64,
		MBED_LPC1765,
		MBED_LPC1766,
		MBED_LPC1768
	} MbedModel;

	FaultInjector();

	virtual ~FaultInjector();

	/*
	 * Tipos de falhas
	 * - Travamento do sistema
	 * - loop infinito
	 * - bit flip
	 */

	void start(float t);
	void crash();

	void infinityLoop();

	//Injetar falha em regiões específicas
	//Injetar falha em regiões aleatórias

	void injectFaultTypeMemoryRegion(MemoryType memType1, MemoryType memType2 =
			DEFAULT, MemoryType memType3 = DEFAULT);

	void injectFaultType(FaultType faultType);

	unsigned int getRandomUInt(unsigned int min, unsigned int max);

	unsigned long getByteUserMemory(unsigned long startAddr,
			unsigned long endAddr);

	char* itoa(char *result, int value, int base);

	MbedModel getMbedModel();

	void startInjectFault();
private:

	void injectFaultTypeMemoryRegionAuxMemoryType(MemoryType memType);
	void injectFault(unsigned long addrStart, unsigned long addrEnd,
			unsigned long changedBytes, uint8_t changedBits);

	MemoryMap *memoryMap;
	unsigned int userMemorySize;
	unsigned int flashMemorySize;
	unsigned int peripheralsMemorySize;
	//Timeout timer;

};

#endif /* FAULTINJECTOR_FAULTINJECTOR_H_ */

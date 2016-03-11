/*
 * FaultInjector.cpp
 *
 *  Created on: 01/03/2016
 *      Author: Cleiton Gon�alves
 */

#include "FaultInjector.h"

FaultInjector::FaultInjector() {

	if (getMbedModel() == MBED_LPC1764) {
		memoryMap = new MemoryMap64();
	} else if (getMbedModel() == MBED_LPC1765
			|| getMbedModel() == MBED_LPC1766) {
		memoryMap = new MemoryMap66_65();
	} else if (getMbedModel() == MBED_LPC1768) {
		memoryMap = new MemoryMap68();
	} else {
		//Indefinido
	}
}

FaultInjector::~FaultInjector() {

}

void FaultInjector::start(float t){
	//timer.attach(this, &FaultInjector::startInjectFault, t);
}

void FaultInjector::startInjectFault(){
	injectFaultType(BIT_FLIPING);
}

void FaultInjector::crash() {

	int *ptr = NULL;
	*ptr = 1;
}

void FaultInjector::infinityLoop() {
	while (true)
		;
}

void FaultInjector::injectFaultType(FaultType faultType) {
	if (faultType == FaultInjector::SYSTEM_CRASH) {
		crash();
	} else if (faultType == FaultInjector::INFINITY_LOOP) {
		infinityLoop();
	}else if(faultType == FaultInjector::BIT_FLIPING){
		injectFaultTypeMemoryRegion(FaultInjector::USER, FaultInjector::PERIPHERALS);
	}
}

void FaultInjector::injectFaultTypeMemoryRegionAuxMemoryType (MemoryType memType){

	unsigned long addrStart, addrEnd;

			if (memType == FaultInjector::FLASH) {
				flashMemorySize = 0;
				for (unsigned int i = 0;
						i < memoryMap->getFlashMemoryRegion().size(); ++i) {
					flashMemorySize +=
							memoryMap->getFlashMemoryRegion().getForIndex(i)->getSize();
				}
				addrStart = getRandomUInt(0, flashMemorySize - 1);
				addrEnd = getRandomUInt(addrStart, flashMemorySize - 1);
				//injectFaulFlashtMemoryRegion(addrStart, addrEnd, DEFAULT_CHANGED_BYTES,DEFAULT_CHANGED_BITS);
			} else if (memType == FaultInjector::USER) {
				userMemorySize = 0;
				for (unsigned int i = 0;
						i < memoryMap->getUserMemoryRegion().size(); ++i) {
					userMemorySize += memoryMap->getUserMemoryRegion().getForIndex(
							i)->getSize();
				}
				addrStart = getRandomUInt(0, userMemorySize - 1);
				addrEnd = getRandomUInt(addrStart, userMemorySize - 1);
				injectFault(addrStart, addrEnd, DEFAULT_CHANGED_BYTES,
						DEFAULT_CHANGED_BITS);
			} else if (memType == FaultInjector::PERIPHERALS) {
				peripheralsMemorySize = 0;

				for (unsigned int i = 0;
						i < memoryMap->getPeripheralsMemoryRegion().size(); ++i) {
					peripheralsMemorySize +=
							memoryMap->getPeripheralsMemoryRegion().getForIndex(i)->getSize();
				}

				addrStart = getRandomUInt(0, peripheralsMemorySize - 1);
				addrEnd = getRandomUInt(addrStart, peripheralsMemorySize - 1);
				injectFault(addrStart, addrEnd,
						DEFAULT_CHANGED_BYTES, DEFAULT_CHANGED_BITS);
			}
}



void FaultInjector::injectFaultTypeMemoryRegion(MemoryType memType1,
		MemoryType memType2, MemoryType memType3) {

if(memType1 != FaultInjector::DEFAULT)
	injectFaultTypeMemoryRegionAuxMemoryType(memType1);
else if(memType2 != FaultInjector::DEFAULT)
injectFaultTypeMemoryRegionAuxMemoryType(memType2);
else if(memType3 != FaultInjector::DEFAULT)
injectFaultTypeMemoryRegionAuxMemoryType(memType3);

}

/**
 * C++ void style "injectFaultMemoryRegiong":
 * Generates a random number (unsigned int) between the minimum
 * and maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 *
 * modified Cleiton Gonçalves
 * referência by Kleber Kruger
 */
void FaultInjector::injectFault(unsigned long addrStart,
		unsigned long addrEnd, unsigned long changedBytes,
		uint8_t changedBits) {

	unsigned char *addr;
	int count, temp, position;

	bool drawn[8]; // bits sorteados (para não alterar o mesmo bit mais de uma vez).

	if (changedBytes < 1 || changedBytes > (addrEnd - addrStart))
		changedBytes = DEFAULT_CHANGED_BYTES;

	if (changedBits > 8) // 0 para automático, 8 para alterar todos os bits
		changedBits = DEFAULT_CHANGED_BITS;

	temp = changedBits;

	for (unsigned long i = 0; i < changedBytes; i++) {

		addr = (unsigned char *) getByteUserMemory(addrStart, addrEnd);

		if (changedBits == 0)
			temp = getRandomUInt(1, 8); // Valor 0 altera n bits automaticamente.

		for (count = 0; count < 8; count++)
			drawn[count] = false;

		count = 0;
		while (count < temp) {
			position = getRandomUInt(0, 7);
			if (drawn[position] != true) {
				drawn[position] = true;
				count++;
				(*addr) ^= (1 << position); // Altera um bit de um endereço (byte) de memória.
			}
		}

	}

}

/**
 * C++ unsigned long style "getRandomUInt":
 * Generates a random number (unsigned int) between the minimum
 * and maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 *
 * modified Cleiton Gonçalves
 * referência by Kleber Kruger
 */

unsigned int FaultInjector::getRandomUInt(unsigned int min, unsigned int max) {
	int k;
	double d;
	d = (double) rand() / ((double) RAND_MAX + 1);
	k = d * (max - min + 1);
	return min + k;
}

/**
 * C++ unsigned long style "getByteUserMemory":
 * modified Cleiton Gonçalves
 * referência by Kleber Kruger
 */

unsigned long FaultInjector::getByteUserMemory(unsigned long startAddr,
		unsigned long endAddr) {

	unsigned long number, limit;
	int i = 0;

	number = getRandomUInt(startAddr, endAddr);
	limit = memoryMap->getUserMemoryRegion()[0]->getSize() - 1;

	while (number > limit) {
		limit += memoryMap->getUserMemoryRegion()[i]->getSize();
		i++;
	}

	return memoryMap->getUserMemoryRegion()[i]->getStart() + (number - limit);
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* FaultInjector::itoa(char *result, int value, int base) {

	// Check that the base if valid
	if (base < 2 || base > 36) {
		*result = '\0';
		return result;
	}

	char *ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ =
				"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35
						+ (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0)
		*ptr++ = '-';
	*ptr-- = '\0';

	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}

	return result;
}

FaultInjector::MbedModel FaultInjector::getMbedModel() {
#if defined(TARGET_LPC1764)
	return MBED_LPC1764;
#elif defined(TARGET_LPC1765)
	return MBED_LPC1765;
#elif defined(TARGET_LPC1766)
	return MBED_LPC1766;
#elif defined(TARGET_LPC1768)
	return MBED_LPC1768;
#else
	return MBED_UNDEFINED;
#endif
}

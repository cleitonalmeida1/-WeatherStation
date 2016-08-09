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

void FaultInjector::start(float t) {
	timer.attach(this, &FaultInjector::startInjectFault, t);
}

void FaultInjector::start(float tMin, float tMax) {
	timer.attach(this, &FaultInjector::startInjectFault,
			getRandomFloat(tMin, tMax));
}

void FaultInjector::startInjectFault() {
	Serial p(USBTX, USBRX);
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
	} else if (faultType == FaultInjector::BIT_FLIPING) {
		injectFaultTypeMemoryRegion(FaultInjector::FLASH);
	}
}

void FaultInjector::injectFaultTypeMemoryRegionAuxMemoryType(
		MemoryType memType) {

	unsigned long addrStart, addrEnd;

	if (memType == FaultInjector::FLASH) {
		flashMemorySize = 0;
		for (unsigned int i = 0; i < memoryMap->getFlashMemoryRegion().size();
				++i) {
			flashMemorySize +=
					memoryMap->getFlashMemoryRegion().getForIndex(i)->getSize();
		}
		injectFaultFlash(DEFAULT_CHANGED_BYTES, DEFAULT_CHANGED_BITS);
	} else if (memType == FaultInjector::USER) {
		userMemorySize = 0;
		for (unsigned int i = 0; i < memoryMap->getUserMemoryRegion().size();
				++i) {
			userMemorySize +=
					memoryMap->getUserMemoryRegion().getForIndex(i)->getSize();
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
		injectFault(addrStart, addrEnd, DEFAULT_CHANGED_BYTES,
				DEFAULT_CHANGED_BITS);
	}
}

void FaultInjector::injectFaultTypeMemoryRegion(MemoryType memType1,
		MemoryType memType2, MemoryType memType3) {

	if (memType1 != FaultInjector::DEFAULT)
		injectFaultTypeMemoryRegionAuxMemoryType(memType1);
	if (memType2 != FaultInjector::DEFAULT)
		injectFaultTypeMemoryRegionAuxMemoryType(memType2);
	if (memType3 != FaultInjector::DEFAULT)
		injectFaultTypeMemoryRegionAuxMemoryType(memType3);

}

/**
 * C++ void style "injectFaultMemoryRegiong":
 * 1ª Escolher um byte da variável mem[] para a inserção de falhas
 * 2ª Sortear a quantidade de bits aleatoriamente para sofre alterações
 * 3ª Sortear o setor da memória flash que será alterado
 * 4ª Aletar somente os bits que não foram alterados
 * 5ª Limpar o setor de memória flash escolhido (Se necessário)
 * 6ª Preparar o setor para a escrita
 * 7ª Copiar a RAM com a falha injetada para o setor da memória flash
 * and maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 *
 * modified Cleiton Gonçalves
 * referência by Kleber Kruger
 */
void FaultInjector::injectFaultFlash(unsigned long changedBytes,
		uint8_t changedBits) {

	char mem[MEM_SIZE]; //memory, it should be aligned to word boundary
	//Sorteia um endereço de memória aleatório para ter seus bits alterados
	int tempMEM = 1;
	int count, temp, position, r;

	bool drawn[8]; // bits sorteados (para não alterar o mesmo bit mais de uma vez).
	changedBytes = DEFAULT_CHANGED_BYTES;

	if (changedBits > 8) // 0 para automático, 8 para alterar todos os bits
		changedBits = DEFAULT_CHANGED_BITS;

	temp = changedBits;

	for (unsigned long i = 0; i < changedBytes; i++) {
		//Sortear um setor da memória flash para injetar falhas
		setorFlash = getRandomUInt(16, 29);
		printf("\n----------------------------------\n");
		printf("\n Injetando falha no Setor \n");
		printf("\n----------------------------------\n");
		printf("%d", setorFlash);
		printf("\n----------------------------------\n");

		if (changedBits == 0)
			temp = getRandomUInt(1, 8); // Valor 0 altera n bits automaticamente.

		for (count = 0; count < 8; count++)
			drawn[count] = false;

		//verificar qual era a situação dos bit antes de sua ateração
		//byte = (unsigned char *) mem[tempMEM];
		//itoa(*byte, str, 2);
		//complete_zero(str);

		//printf("\n Setor: \n");
		//printf("%d", setorFlash);
		//printf("\n----------------------------------\n");
		//printf("Endereco na memoria:");
		//printf("%x ", (unsigned long) byte);
		//printf("\n----------------------------------\n");
		//printf("Como esta armazenado");
		//printf("\n----------------------------------\n");
		//printf("%s", str);
		//printf("\n----------------------------------\n");

		printf(
				"  user reserved flash area: start_address=0x%08X, size=%d bytes\r\n",
				sector_start_adress[setorFlash],
				setorFlash > 15 ?
				FLASH_SECTOR_SIZE_16_TO_29 :
									FLASH_SECTOR_SIZE_0_TO_15);

		//printf("  read_BootVer=0x%08X\r\r\n", iap.read_BootVer());

		printf("\n----------------------------------\n");

		//for (int i = 0; i < MEM_SIZE; i++)
		//mem[i] = i & 0xFF;

		r = iap.blank_check(setorFlash, setorFlash);
		//printf("blank check result = 0x%08X\r\n", r);

		//  erase sector, if required

		if (r == SECTOR_NOT_BLANK) {
			iap.prepare(setorFlash, setorFlash);
			r = iap.erase(setorFlash, setorFlash);
			printf("erase result       = 0x%08X\r\n", r);
		}

		// copy RAM to Flash
		iap.prepare(setorFlash, setorFlash);
		//bytes antes da escrita
		memdump(sector_start_adress[setorFlash], MEM_SIZE / 2);

		r = iap.write(mem, sector_start_adress[setorFlash], MEM_SIZE);
		printf(
				"copied: SRAM(0x%08X)->Flash(0x%08X) for %d bytes.",
				mem, sector_start_adress[setorFlash], MEM_SIZE/2, r);

		// compare
		r = iap.compare(mem, sector_start_adress[setorFlash], MEM_SIZE);
		//printf("compare result     = \"%s\"\r\n", r ? "FAILED" : "OK");

		//bytes após a escrita
		memdump(sector_start_adress[setorFlash], MEM_SIZE / 2);

	}
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
void FaultInjector::injectFault(unsigned long addrStart, unsigned long addrEnd,
		unsigned long changedBytes, uint8_t changedBits) {
	unsigned char *addr;
	int count, temp, position;

	bool drawn[8]; // bits sorteados (para não alterar o mesmo bit mais de uma vez).

	if (changedBytes < 1 || changedBytes > (addrEnd - addrStart))
		changedBytes = DEFAULT_CHANGED_BYTES;

	if (changedBits > 8) // 0 para automático, 8 para alterar todos os bits
		changedBits = DEFAULT_CHANGED_BITS;

	temp = changedBits;

	//verificar qual era a situação dos bit antes de sua ateração
	str[10];
	byte = (unsigned char *) addr;
	itoa(*byte, str, 2);
	complete_zero(str);

	/* começou assim
	 printf("--------------ANTES---------------\n");
	 printf("Endereco na memoria:\n");
	 printf("%ld ", (unsigned long) byte);
	 printf("----------------------------------\n");
	 printf("Como esta armazenado");
	 printf("----------------------------------\n");
	 printf("%s\n", str);
	 printf("----------------------------------\n");
	 */
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
		//verificar qual era a situação dos bit antes de sua ateração
		byte = (unsigned char *) addr;
		itoa(*byte, str, 2);
		complete_zero(str);

		printf("\n----------------------------------\n");
		printf("Endereco na memoria:");
		printf("%ld ", (unsigned long) byte);
		printf("\n----------------------------------\n");
		printf("Como esta armazenado");
		printf("\n----------------------------------\n");
		printf("%s", str);
		printf("\n----------------------------------\n");

	}

}

/**
 * Completa um byte com zeros
 * maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 */
unsigned char* FaultInjector::complete_zero(unsigned char *num_str) {
	int i;
	int len = strlen((const char *) num_str);
	memmove(num_str + (8 - len), num_str, len);
	for (i = 0; i < (8 - len); i++) {
		num_str[i] = '0';
	}
	return num_str;
}

/**
 * Generates a random number (float) between the minimum and
 * maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 */
float FaultInjector::getRandomFloat(float min, float max) {
	int rd = (int) getRandomDouble((int) (min * 10), (int) (max * 10) + 1);
	return (float) rd / 10;
}

/**
 * Generates a random number (double) between the minimum and
 * maximum range.
 *
 * @param min - minimum
 * @param max - maximum
 */
double FaultInjector::getRandomDouble(double min, double max) {
	double d, k;
	d = (double) rand() / ((double) RAND_MAX + 1);
	k = d * (max - min + 1);
	return min + k;
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
 *
 */
void FaultInjector::memdump(char *base, int n) {
	unsigned int *p;

	printf("  memdump from 0x%08X for %d bytes", (unsigned long) base, n);

	p = (unsigned int *) ((unsigned int) base & ~(unsigned int) 0x3);

	for (int i = 0; i < (n >> 2); i++, p++) {
		if (!(i % 4)) {
			printf("\r\n  0x%08X :", (unsigned int) p);
		}
		byte = (unsigned char *) p;
		itoa(*byte, str, 2);
		complete_zero(str);

		////printf(" 0x%08X %s", *p, str);
		if (i % 2 == 0) {
			printf(" %s", str);
		}
	}

	printf("\r\n");
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
unsigned char* FaultInjector::itoa(int value, unsigned char *result, int base) {

	if (base < 2 || base > 36) {
		*result = '\0';
		return result;
	}

	unsigned char *ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ =
				"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35
						+ (tmp_value - value * base)];
	} while (value);

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

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* FaultInjector::itoa(int value, char *result, int base) {

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

/*
 * MemoryMap6665.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYMAP66_65_H_
#define MEMORYMAP_MEMORYMAP66_65_H_

#include "mbed.h"
#include "MemoryMap.h"
#include "DataStruct/ArrayList.h"
#include "MemoryRegion.h"

class MemoryMap66_65: public MemoryMap {
public:
	MemoryMap66_65() :
			userMemory32(0X10000000, 0X10008000 - 1, MemoryRegion::USER,
					"userMemory_32_SRAM_66_65"), userMemory16R(0x2007C000,
					0x20004000 - 1, MemoryRegion::USER,
					"userMemory_16_SRAM_66_65"), userMemory16R1(0x20004000,
					0x20084000 - 1, MemoryRegion::USER,
					"userMemory_16_SRAM1_66_65"), flashMemory256(0x00000000,
					0x00040000 - 1, MemoryRegion::FLASH, "flashMemory_265_KB") {
		userMemoryMap66_65.add(&userMemory32);
		userMemoryMap66_65.add(&userMemory16R);
		userMemoryMap66_65.add(&userMemory16R1);
		flashMemoryMap66_65.add(&flashMemory256);

	}

	virtual ArrayList<MemoryRegion*> getUserMemoryRegion() {
		return userMemoryMap66_65;
	}

	virtual ArrayList<MemoryRegion*> getFlashMemoryRegion() {
		return flashMemoryMap66_65;
	}

	virtual ~MemoryMap66_65(){

	}

private:
	MemoryRegion userMemory32;
	MemoryRegion userMemory16R;
	MemoryRegion userMemory16R1;
	MemoryRegion flashMemory256;
	ArrayList<MemoryRegion*> userMemoryMap66_65;
	ArrayList<MemoryRegion*> flashMemoryMap66_65;
};

#endif /* MEMORYMAP_MEMORYMAP66_65_H_ */

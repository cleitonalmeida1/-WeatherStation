/*
 * MemoryMapPeripherals.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYMAPPERIPHERALS_H_
#define MEMORYMAP_MEMORYMAPPERIPHERALS_H_

#include "MemoryMap.h"
#include "MemoryRegion.h"

class MemoryMapPeripherals{
public:
	MemoryMapPeripherals() :
			papb0(0x40000000, 0x40080000 - 1, MemoryRegion::PERIPHERALS,
					"PeripheralsAPB0"),
			papb1(0x40080000, 0x40100000 - 1,
					MemoryRegion::PERIPHERALS, "PeripheralsAPB1"),
					pbba(0x42000000, 0x44000000 - 1, MemoryRegion::PERIPHERALS,
					"PeripheralsBitBandAlias"),
			pahb(0x50000000,0x50200000 - 1, MemoryRegion::PERIPHERALS,
					"AHBPeripherals"),
					ppb(0xE0000000, 0xE0100000 - 1,MemoryRegion::PERIPHERALS, "PrivatePeripheralsBus") {

		memoryMap.add(&papb0);
		memoryMap.add(&papb1);
		memoryMap.add(&pbba);
		memoryMap.add(&pahb);
		memoryMap.add(&ppb);
	}

	ArrayList<MemoryRegion*> getPeripheralsMemoryRegion() {
		return memoryMap;
	}

	virtual ~MemoryMapPeripherals(){

	}

private:
	MemoryRegion papb0;
	MemoryRegion papb1;
	MemoryRegion pbba;
	MemoryRegion pahb;
	MemoryRegion ppb;
	ArrayList<MemoryRegion*> memoryMap;

};

#endif /* MEMORYMAP_MEMORYMAPPERIPHERALS_H_ */

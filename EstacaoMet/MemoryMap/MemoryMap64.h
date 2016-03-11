/*
 * MemoryMap64.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYMAP64_H_
#define MEMORYMAP_MEMORYMAP64_H_

#include  "DataStruct/ArrayList.h"
#include "MemoryMap.h"
#include "MemoryRegion.h"
#include "mbed.h"

class MemoryMap64: public MemoryMap {
public:
	MemoryMap64() :
			memoryUser16(0x10000000, 0x10004000 - 1, MemoryRegion::USER,
					"memory_User_64"), memoryUserAhb16(0x2007C000,
					0x20004000 - 1, MemoryRegion::USER, "memory_User_Ahb_64"), flash(
					0x00000000, 0x00020000 - 1, MemoryRegion::USER, "flash_64") {

		userMemoryMap1764.add(&memoryUser16);
		userMemoryMap1764.add(&memoryUserAhb16);
		flashMemoryMap1764.add(&flash);
	}

	virtual ArrayList<MemoryRegion*> getUserMemoryRegion() {
		return userMemoryMap1764;
	}

	virtual ArrayList<MemoryRegion*> getFlashMemoryRegion() {
		return flashMemoryMap1764;
	}

	virtual ~MemoryMap64(){

	}
private:
	ArrayList<MemoryRegion*> userMemoryMap1764;
	ArrayList<MemoryRegion*> flashMemoryMap1764;
	MemoryRegion memoryUser16;
	MemoryRegion memoryUserAhb16;
	MemoryRegion flash;
};

#endif /* MEMORYMAP_MEMORYMAP64_H_ */

/*
 * MemoryMap.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYMAP_H_
#define MEMORYMAP_MEMORYMAP_H_

#include  "DataStruct/ArrayList.h"
#include "MemoryRegion.h"
#include "mbed.h"
#include "MemoryMapPeripherals.h"



class MemoryMap {
public:
	MemoryMap() {
		for (unsigned int i = 0; i < map.getPeripheralsMemoryRegion().size();
				++i) {
			peripheralsMemoryRegion.add(
					map.getPeripheralsMemoryRegion().getForIndex(i));
		}
	}

	virtual ArrayList<MemoryRegion*> getUserMemoryRegion() = 0;
	virtual ArrayList<MemoryRegion*> getFlashMemoryRegion() = 0;
	virtual ArrayList<MemoryRegion*> getPeripheralsMemoryRegion() {
		return peripheralsMemoryRegion;
	}

	virtual ~MemoryMap() {

	}

private:
	MemoryMapPeripherals map;
	ArrayList<MemoryRegion*> peripheralsMemoryRegion;
};

#endif /* MEMORYMAP_MEMORYMAP_H_ */

/*
 * MemoryRegion.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYREGION_H_
#define MEMORYMAP_MEMORYREGION_H_

#include "mbed.h"

class MemoryRegion {
public:

	typedef enum {
		FLASH, USER, PERIPHERALS
	} MemoryRegionType;

	MemoryRegion(unsigned long start, unsigned long end, MemoryRegionType type,
			const char* name = "") :
			start(start), end(end), size(end - start), type(type), name(name) {
	}

	virtual ~MemoryRegion() {
	}

	bool operator==(MemoryRegion m) {
		return true;
	}

	unsigned long getStart() {
		return start;
	}

	unsigned long getEnd() {
		return end;
	}

	unsigned long getSize() {
		return size;
	}

	const char* getName() {
		return name;
	}

	void setName(const char* name) {
		this->name = name;
	}

	MemoryRegionType getType() {
		return type;
	}
private:

	unsigned long start;
	unsigned long end;
	unsigned long size;
	MemoryRegionType type;
	const char* name;
};

#endif /* MEMORYMAP_MEMORYREGION_H_ */

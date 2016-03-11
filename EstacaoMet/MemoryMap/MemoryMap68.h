/*
 * MemoryMap68.h
 *
 *  Created on: 02/03/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef MEMORYMAP_MEMORYMAP68_H_
#define MEMORYMAP_MEMORYMAP68_H_

#include "mbed.h"
#include "MemoryMap.h"
#include "DataStruct/ArrayList.h"
#include "MemoryRegion.h"

class MemoryMap68: public MemoryMap {
public:
	MemoryMap68() : userMemory32(0X10000000, 0X10008000 - 1, MemoryRegion::USER,
				"userMemory_32_SRAM_68"),
				userMemory16R(0x2007C000, 0x20004000 - 1, MemoryRegion::USER, "userMemory_16_SRAM_68"),
				userMemory16R1(0x20004000, 0x20084000 - 1, MemoryRegion::USER, "userMemory_16_SRAM1_68"),
				flashMemory512(0x00000000, 0x00080000 - 1, MemoryRegion::FLASH, "flashMemory_512_SRAM1_68")
				{
			userMemoryMap68.add(&userMemory32);
			userMemoryMap68.add(&userMemory16R);
			userMemoryMap68.add(&userMemory16R1);
			flashMemoryMap68.add(&flashMemory512);
		}

		virtual ArrayList<MemoryRegion*> getUserMemoryRegion(){
			return userMemoryMap68;
		}

		virtual ArrayList<MemoryRegion*> getFlashMemoryRegion(){
			return flashMemoryMap68;
		}

		virtual ~MemoryMap68(){

		}
	private:
		MemoryRegion userMemory32;
		MemoryRegion userMemory16R;
		MemoryRegion userMemory16R1;
		MemoryRegion flashMemory512;
		ArrayList<MemoryRegion*> userMemoryMap68;
		ArrayList<MemoryRegion*> flashMemoryMap68;
};

#endif /* MEMORYMAP_MEMORYMAP68_H_ */

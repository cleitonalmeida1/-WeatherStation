/*
 * FaultInjector.cpp
 *
 *  Created on: 01/03/2016
 *      Author: Cleiton Gonçalves
 */


#include "FaultInjector.h"

FaultInjector::FaultInjector() {
	// TODO Auto-generated constructor stub

}

FaultInjector::~FaultInjector() {
	// TODO Auto-generated destructor stub
}


void FaultInjector::crash(long t){

	int *ptr = NULL;
	*ptr = 1;
}

void FaultInjector::infinityLoop(long t){
		while(true);
}

void FaultInjector::inject(long t){

}

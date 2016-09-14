/*
 * Main.cpp
 *
 *  Created on: 22/07/2016
 *      Author: Cleiton GonÃ§alves
 */

#include "ResultStateWTApp.h"
unsigned short Sort::cont = 0;
unsigned short Sort::array[Sort::n];
Timer Sort::t;
LocalFileSystem Sort::localFileSystem("local");
Logger Sort::logger("/local/log.txt", false);
ConfigFile Sort::configFile("/local/settings.txt");
FaultInjector Sort::f;
unsigned long Sort::ini = (unsigned long) 0x10000000;
unsigned long Sort::fim = (unsigned long) 0x10008000 - 1;

int main() {

	Application::initialize<SortApp>();

	return 0;
}

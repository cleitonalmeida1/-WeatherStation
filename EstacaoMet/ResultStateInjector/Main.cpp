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
Logger Sort::logger("/local/log.csv", false);


int main() {

	Application::initialize<SortApp>();

	return 0;
}

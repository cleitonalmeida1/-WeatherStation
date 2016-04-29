#include "mbed.h"
#include "WeatherStation.h"

DigitalOut myled(LED3);
Serial pc(USBTX, USBRX);

using namespace std;

int main() {

	WeatherStation w;
	w.getInstance()->start();
}

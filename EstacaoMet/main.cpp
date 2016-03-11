#include "mbed.h"

DigitalOut myled(LED1);

using namespace std;

int main() {

	while(1) {
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
    }

}

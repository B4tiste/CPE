#include "MicroBit.h"
#include "neopixel.h"

#define ROUGE uBit.io.P0
#define ORANGE uBit.io.P1
#define VERT uBit.io.P2

MicroBit uBit;

Neopixel neo = Neopixel(MICROBIT_PIN_P0, 1);

void sleep(int temp);

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    neo.clear();

    neo.setColor(0, 255, 120, 50);
    neo.show();

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}

void sleep(int temp)
{
    uBit.sleep(temp);
}
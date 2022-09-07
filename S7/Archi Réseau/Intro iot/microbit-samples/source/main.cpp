#include "MicroBit.h"

MicroBit uBit;
MicroBitThermometer termo;


int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    int cpt = 0;

    while(true)
    {
        int x = uBit.accelerometer.getRoll();
        if (x < 0)
        {
            cpt++;
        }
        
        uBit.display.scroll(cpt, 50);

        uBit.sleep(500);
    }

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}


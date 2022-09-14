#include "MicroBit.h"

#define ROUGE uBit.io.P0
#define ORANGE uBit.io.P1
#define VERT uBit.io.P2

MicroBit uBit;
void sleep(int temp);

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.display.scroll("init");

    ROUGE.setDigitalValue(1);
    ORANGE.setDigitalValue(1);
    VERT.setDigitalValue(1);

    sleep(500);

    ROUGE.setDigitalValue(0);
    ORANGE.setDigitalValue(0);
    VERT.setDigitalValue(0);

    sleep(250);

    while (true)
    {
        
        ROUGE.setDigitalValue(1);

        sleep(1000);

        ROUGE.setDigitalValue(0);
        VERT.setDigitalValue(1);

        sleep(500);

        VERT.setDigitalValue(0);
        ORANGE.setDigitalValue(1);

        sleep(300);

        ORANGE.setDigitalValue(0);

    }
    

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}

void sleep(int temp)
{
    uBit.sleep(temp);
}
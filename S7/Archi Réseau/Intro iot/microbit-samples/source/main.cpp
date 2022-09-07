#include "MicroBit.h"


MicroBit uBit;
MicroBitThermometer termo;

void onButton(MicroBitEvent e)
{
    if (e.source == MICROBIT_ID_BUTTON_A)
        uBit.display.scroll("A");
        

    if (e.source == MICROBIT_ID_BUTTON_B)
        uBit.display.scroll("B"); 
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButton);

    // Insert your code here!
    int temp = termo.getTemperature();
    if(temp > 30)
    {
        ManagedString display = "tro cho:" + ManagedString(temp) + "C";
        uBit.display.scroll(display.toCharArray());
    }
    else
    {
        uBit.display.scroll(temp);
    }

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}


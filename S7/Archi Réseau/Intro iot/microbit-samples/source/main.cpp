#include "MicroBit.h"

MicroBit uBit;
MicroBitThermometer termo;

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.radio.enable();
    uBit.radio.setGroup(14);

    uBit.display.scroll("init");

    while(1)
    {
        if (uBit.buttonA.isPressed())
        {
            uBit.radio.datagram.send("/b/123");
        }

        else if (uBit.buttonB.isPressed())
        {
            uBit.radio.datagram.send("/b/456");
        }

        uBit.sleep(100);
    }

}


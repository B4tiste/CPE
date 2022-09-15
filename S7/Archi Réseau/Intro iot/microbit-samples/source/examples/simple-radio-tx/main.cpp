#include "MicroBit.h"

MicroBit    uBit;

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.radio.enable();

    while(1)
    {
        if (uBit.buttonA.isPressed())
            uBit.radio.datagram.send("1");

        else if (uBit.buttonB.isPressed())
            uBit.radio.datagram.send("2");

        uBit.sleep(100);
    }

}


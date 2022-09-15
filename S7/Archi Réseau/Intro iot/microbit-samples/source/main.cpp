#include "MicroBit.h"

#define PREFIX "/b/"

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
        int temp = termo.getTemperature();

        PacketBuffer b(1);
        b[0] = temp;

        // ManagedString string_temp = ManagedString(temp);
        if(uBit.buttonA.isPressed()){
            uBit.display.scroll(temp);
        }

        uBit.radio.datagram.send(b);

        uBit.sleep(1000);
    }

}


#include "MicroBit.h"

MicroBit    uBit;

void onData(MicroBitEvent)
{
    ManagedString s = uBit.radio.datagram.recv();

    if (s == "1")
        uBit.display.print("A");

    if (s == "2")
        uBit.display.print("B");
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.radio.setGroup(14);

    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();

    while(1)
        uBit.sleep(1000);
}


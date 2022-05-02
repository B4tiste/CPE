int sw = 0;
void Config_Timer4(void)
{
    T4CON &= ~(1 << 2);
    T4CON |= (1 << 1);

    T4CON &= ~(1 << 7);
    T4CON &= ~(1 << 6);
    T4CON &= ~(1 << 0);
    T4CON &= ~(1 << 3);

    RCAP4 = 65536 - 65;
    T2 = 65535 - 37;
    T4CON |= (1 << 2);

    EIP2 |= (1 << 2);
    EIE2 |= (1 << 2);
}

void ISR_Timer4(void) interrupt 16
{
    Flag_T4 = 1;
    if (T4CON & (1 << 7))
    {
        T4CON &= ~(1 << 7);
        if (sw != 0)
        {
            RCAP4 = 65535 - 65;
            SIG_OUT = 0;
            sw = 0;
        }
        else
        {
            RCAP4 = 65535 - 35;
            SIG_OUT = 1;
            sw = 1;
        }
    }
    if (T4CON & (1 << 6))
        T4CON &= ~(1 << 6); // S�curit� si INT EXF4
    Flag_T4 = 0;
}
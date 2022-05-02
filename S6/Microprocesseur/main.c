
#define ACTIF 1
#define INACTIF 0

// GPIO
sbit LED = P1 ^ 6; // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;
sbit SIG_OUT = P1 ^ 0;
sbit Flag_T2 = P6 ^ 6;

void Config_Timer2();
void INTERRUPT_TIMER2();

int main(int argc, char const *argv[])
{
    bool clignotement = true;

    BP = 1;

    // Phase de démarrage
    while (clignotement)
    {
        if (BP == ACTIF)
        {
            clignotement = false;
            LED = 0;
        }
        else
        {
            LED = ~LED;
            fct_tempo(50000);
        }
    }

    P1MDOUT |= (1 << 0); // P1.0 en sortie

    SIG_OUT = 0;
    Flag_T2 = 0;

    Config_Timer2();

    // Activation des interruptions
    EA = 1;

    // Phase usage
    while (1)
    {
        /*
            Mise en place d'un rapport cyclique de 35%
            https://cdn.discordapp.com/attachments/962750320788766810/970662894687629342/unknown.png
        */
        PCA0CPL1 = 0x0;
        PCA0CPH1 = 0x58; // 35% en Hexa
    }

    return 0;
}

void Config_Timer2()
{
    // Configurer T2CON CKCON RCAP2L RCAP2H TL2 et TH2
    CKCON &= 0xdf; // T2M: Timer 2 Clock Select
                   // CLK = sysclk/12
    TF2 = 0;       // RAZ Flag TF2 Overflow Timer2
    EXF2 = 0;      // RAZ Flag EXF2
    EXEN2 = 0;     // Action entr�e T2EX d�valid�e
    CT2 = 0;       // Mode Timer
    CPRL2 = 0;     // Auto reload of timer 2
                   // On a utilis� l��criture Bit � bit sur T2CON

    RCAP2 = -(((SYSCLK / 12) / 480)); // Timer de 480 Hz
    T2 = RCAP2;                       // pour un premier cycle de bonne dur�e
    TR2 = 1;                          // Timer2 d�marr�
    PT2 = 1;                          // INT Timer2 priorit� haute
    ET2 = 1;                          // INT Timer2 autoris�e
}

void INTERRUPT_TIMER2() interrupt 5
{
    Flag_T2 = 1;

    SIG_OUT = ~SIG_OUT;

    // RAZ Timer2
    TF2 = 0;
    EXF2 = 0;

    Flag_T2 = 0;
}

void confT4()
{
    T4CON &= ~0xCD;
    T4CON |= 0x02;
    T4CON |= 0x04;

    EIP2 |= (1 << 2); // PT4=1 -- Int Timer4 priorit� haute
    EIE2 |= (1 << 2); // ET4=1 -- Interruption T4 autoris�e

    RCAP4 = 65535 - X;
}
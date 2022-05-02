//------------------------------------------------------------------------------------
// Base_TP3_IRC
//------------------------------------------------------------------------------------
//
// AUTH: FJ
// DATE: 03-03-2009
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h> // SFR declarations
//------------------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//------------------------------------------------------------------------------------
sfr16 TMR3RL = 0x92; // Timer3 reload value
sfr16 TMR3 = 0x94;   // Timer3 counter
sfr16 ADC0 = 0xbe;   // ADC0 data
sfr16 ADC0GT = 0xc4; // ADC0 greater than window
sfr16 ADC0LT = 0xc6; // ADC0 less than window
sfr16 RCAP2 = 0xca;  // Timer2 capture/reload
sfr16 T2 = 0xcc;     // Timer2
sfr16 RCAP4 = 0xe4;  // Timer4 capture/reload
sfr16 T4 = 0xf4;     // Timer4
sfr16 DAC0 = 0xd2;   // DAC0 data
sfr16 DAC1 = 0xd5;   // DAC1 data

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400 // approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

extern code char Sin_table[];
unsigned char CP_BCL = 1;

// El�ments pr�sents sur la carte 8051F020
sbit LED = P1 ^ 6; // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;  // Bouton Poussoir '1' relach�, '0' press�

// El�ments de l'application Pilotage d'un syst�me de tri
sbit Tst4 = P3 ^ 4;
sbit Tst5 = P3 ^ 5;
sbit Tst6 = P3 ^ 6;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void);       // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void Config_INT7(void);

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void)
{

    unsigned char i;
    Init_Device();
    Config_INT7();

    // Correction Sorties LED et Tst4 mise en Push Pull
    P1MDOUT |= (1 << 6);            // LED P1.6 en PushPull
    P3MDOUT |= (1 << 4) | (1 << 6); // TST4 P3.4 et P3.6 en PushPull
    P74OUT |= (1 << 0) | (1 << 1);  // P4 en PushPull  (impossible de configurer bit � bit)

    CP_BCL = 0;
    Tst4 = 0;
    Tst6 = 0;
    LED = LED_Off;
    // Activit� 2 - Configuration du Bouton Poussoir P3.7
    // BP actif niveau bas
    // LED allum�e si LED est au niveau haut

    // Configuration de BP (P3.7) en entr�e
    BP = 1;
    P3MDOUT &= ~0x80; // P3.7 plac� en Open Drain

    EA = 1;

    while (1)
    {
        LED = ~LED;
        Tst4 = ~Tst4;
        if (Tst4 == 0)
            P4 &= ~((1 << 1) | (1 << 6));
        else
            P4 |= ((1 << 1) | (1 << 6));
        //   if (BP != 0)  LED = ~LED;
        //   else LED = 0;
        for (i = 0; i <= CP_BCL; i++)
            fct_tempo(60000);
    }
}
//***************************************************************************************
void Config_INT7(void)
{
    // Registres: P3IF
    P3IF &= ~0x08; // INT7 active front descendant
    P3IF &= ~0x80; // RAZ Flag INT7
    EIE2 |= 0x20;  // INT7 autoris�e
    EIP2 &= ~0x20; // Priorit� basse
}
//***************************************************************************************
void ISR_INT7(void) interrupt 19
{

    Tst6 = 1;
    P3IF &= ~0x80; // RAZ Flag INT7
    if (CP_BCL == 1)
        CP_BCL = 10;
    else
        CP_BCL = 1;
    Tst6 = 0;
}

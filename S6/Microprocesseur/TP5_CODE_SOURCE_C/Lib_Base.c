//******************************************************************************
//TP_8051_Lib.asm
//   Ce fichier contient des définitions et des routines utiles au TP
//  Microcontrôleur
//  Aucune modification n'est nécessaire.
//  Il suffit d'ajouter ce fichier à votre Projet
//  TARGET MCU  :  C8051F020 

//******************************************************************************

#include "C8051F020.h"

// Peripheral specific initialization functions,
// Called from the Init_Device() function

//-----------------------------------------------------------------------------
// Dévalidation du watchdog
//-----------------------------------------------------------------------------
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
}

//-----------------------------------------------------------------------------
// Configuration des Ports d'entrée-sorties
//-----------------------------------------------------------------------------

void Port_IO_Init()
{
    // P0.0  -  TX0 (UART0), Push-Pull, Digital
    // P0.1  -  RX0 (UART0), Open-Drain, Digital
    // P0.2  -  TX1 (UART1), Push-Pull, Digital
    // P0.3  -  RX1 (UART1), Open-Drain, Digital
    // P0.4  -  T0 (Timer0), Open-Drain, Digital
    // P0.5  -  INT0 (Tmr0), Open-Drain, Digital
    // P0.6  -  T1 (Timer1), Open-Drain, Digital
    // P0.7  -  INT1 (Tmr1), Open-Drain, Digital

    // P1.0  -  T2 (Timer2), Open-Drain, Digital
    // P1.1  -  T2EX (Tmr2), Open-Drain, Digital
    // P1.2  -  T4 (Timer4), Open-Drain, Digital
    // P1.3  -  T4EX (Tmr4), Open-Drain, Digital
    // P1.4  -  SYSCLK,      Push-Pull, Digital  Visu Horloge Système
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  General Purpose I/O, Push-Pull, Digital   Port LED
    // P1.7  -  General Purpose I/O, Open-Drain, Digital

    P0MDOUT   = (1<<0)|(1<<2); 
    P1MDOUT   = (1<<4)|(1<<6);
   
    P3MDOUT   = 0x00;
    P74OUT    = 0x00;
    P1MDIN    = 0xFF;

    XBR0      = 0x04;
    XBR1      = 0xFE;
    XBR2      = 0x5C;
}

//-----------------------------------------------------------------------------
// Configuration de l'oscillateur - SYSCLK = Clock externe 22118400Hz 
//-----------------------------------------------------------------------------
void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}


//-----------------------------------------------------------------------------
// Initialisation globale du Microcontrôleur - 
//-----------------------------------------------------------------------------
void Init_Device(void)
{
    Reset_Sources_Init();
    Port_IO_Init();
    Oscillator_Init();
}

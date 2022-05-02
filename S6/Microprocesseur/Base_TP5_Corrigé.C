//------------------------------------------------------------------------------------
// Base_TP4_IRC
//------------------------------------------------------------------------------------
//
// AUTH: FJ
// DATE: 03-03-2022
// Target: C8051F02x
//
// Tool chain: KEIL Eval 'c'
//
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h> // SFR declarations
#include <stdio.h>
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

#define SYSCLK 22118400L // approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

#define BAUDRATE 19200L
#define Freq_timer0 (BAUDRATE * 16)

#define Preload_Timer1 (SYSCLK / Freq_timer0)
#if Preload_Timer1 > 255
#error "Valeur Preload Timer0 HORS SPECIFICATIONS"
#endif

// El�ments pr�sents sur la carte 8051F020
sbit LED = P1 ^ 6; // LED verte: '1' = ON; '0' = OFF
sbit BP = P3 ^ 7;  // Bouton Poussoir '1' relach�, '0' press�

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device(void);       // Fonction cod�e dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur cod�e dans Asm_8051_Lib.asm
void CFG_Clock_UART0(void);
void CFG_UART0(void);
char getkey_one_time(void);

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main(void)
{

    char temp_char;
    unsigned int CP_BCL;
    unsigned char CP;
    char xdata buf[20];
    unsigned char i;

    // Configurations globales
    Init_Device();
    CFG_Clock_UART0();
    CFG_UART0();

    // Configurations des Sorties GPIO

    // Initialisations des sorties
    LED = LED_Off;
    CP_BCL = 0;
    CP = 0;

    // Boucle infinie
    while (1)
    {
        LED = ~LED;
        fct_tempo(50000);

// Pour compiler une activit�, il faut qu'elle soit encadr�e par un "#If 1 // # endif"
// Inversement toute activit� encadr�e par un "#If 0 // # endif" ne sera pas compil�e

// Activit� 2 - Test config UART - Test Transmission - Envoi continu
#if 1
        SBUF0 = 'A';
#endif

// Activit� 3 - Test config UART - Test r�ception
#if 0  
					  if (RI0)
					  {
							 temp_char = SBUF0;
					     SBUF0 = temp_char+1;
					     RI0 = 0;
						}
#endif
// Activit� 4  Putchar - utilisation de printf
#if 0		 
					    CP++;
						  if (CP>=10)
						  {   
								  CP = 0;
							    printf("Compteur: %u\n",CP_BCL);
								  CP_BCL++;
              }

#endif
// Etape 5 - Codage Getkey - utilisation de gets
#if 0	
             gets(buf,sizeof(buf)-1);
             for(i=0;i<sizeof(buf);i++)
						 { if (buf[i] !=0) buf[i]++; }
						 printf("reponse: %s\n",buf);
#endif
    }
}
//*****************************************************************************
// CFG_clock_UART
//	Utilisation du Timer 1
//
//
//*****************************************************************************
void CFG_Clock_UART0(void)
{
    CKCON |= (1 << 4); // T1M: Timer 1 Clock Select
                       // Timer CLK = SYSCLK

    TMOD |= (1 << 5);
    TMOD &= ~((1 << 7) | (1 << 6) | (1 << 4)); // Timer1 configur� en Timer 8 bit avec auto-reload
    TF1 = 0;                                   // Flag Timer effac�
    TH1 = -(Preload_Timer1);
    ET1 = 0; // Interruption Timer 1 d�valid�e
    TR1 = 1; // Timer1 d�marr�
}
//*****************************************************************************
// CFG_uart0_mode1
//
//
//
//*****************************************************************************
void CFG_UART0(void)
{
    RCLK0 = 0; // Source clock Timer 1
    TCLK0 = 0;
    PCON |= (1 << 7);  // SMOD0: UART0 Baud Rate Doubler Disabled.
    PCON &= ~(1 << 6); // SSTAT0=0
    SCON0 = 0x70;      // Mode 1 - Check Stop bit - Reception valid�e

    //   TI0 = 0;     // Drapeaux TI et RI � z�ro
    RI0 = 0;
    TI0 = 1; //� cause du codage de putchar

    ES0 = 0; // Interruption UART autoris�e
}
//*****************************************************************************
char putchar(char c)
{
    while (TI0 == 0)
        ;
    TI0 = 0;
    SBUF0 = c;
    return c;
}

//*****************************************************************************
char _getkey(void)
{
    char c;
    while (RI0 == 0)
        ;
    RI0 = 0;
    c = SBUF0;
    return c;
}

//*****************************************************************************
// Inutile dans ce TP IRC
char getkey_one_time(void)

{
    char c;
    if (RI0 == 0)
        return 0;
    else
    {
        RI0 = 0;
        return SBUF0;
    }
}

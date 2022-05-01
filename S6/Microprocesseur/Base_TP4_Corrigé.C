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
#include <c8051f020.h>                    // SFR declarations
//------------------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F02x
//------------------------------------------------------------------------------------
sfr16 TMR3RL   = 0x92;                    // Timer3 reload value
sfr16 TMR3     = 0x94;                    // Timer3 counter
sfr16 ADC0     = 0xbe;                    // ADC0 data
sfr16 ADC0GT   = 0xc4;                    // ADC0 greater than window
sfr16 ADC0LT   = 0xc6;                    // ADC0 less than window
sfr16 RCAP2    = 0xca;                    // Timer2 capture/reload
sfr16 T2       = 0xcc;                    // Timer2
sfr16 RCAP4    = 0xe4;                    // Timer4 capture/reload
sfr16 T4       = 0xf4;                    // Timer4
sfr16 DAC0     = 0xd2;                    // DAC0 data
sfr16 DAC1     = 0xd5;                    // DAC1 data

//------------------------------------------------------------------------------------
// Global CONSTANTS
//------------------------------------------------------------------------------------

#define SYSCLK 22118400L //approximate SYSCLK frequency in Hz
#define LED_On 1
#define LED_Off 0

// Eléments présents sur la carte 8051F020
sbit  LED = P1^6;         // LED verte: '1' = ON; '0' = OFF
sbit BP = P3^7;           // Bouton Poussoir '1' relaché, '0' pressé

// GPIO spécifques pour ce TP
sbit Flag_BCL = P2^0;
sbit Flag_T2 = P2^4;
sbit Flag_T4 = P2^6;
sbit SIG_OUT = P3^0;

//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void Init_Device (void); // Fonction codée dans LIB_Base.c
void fct_tempo(unsigned int); // Fonction assembleur codée dans Asm_8051_Lib.asm
void Config_Timer2();
void Config_Timer4();

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main (void) {

	Init_Device();

// Configurations des Sorties GPIO
	P2MDOUT   = (1<<0); // P2.0 (Flag_BCL) en Push Pull
	P2MDOUT  |= (1<<4)|(1<<6);  // P2.4 (Flag_T2) et P2.6 (Flag_T4)  en Push Pull
	P3MDOUT |= (1<<0); // P3.0 (SIG_OUT) en sortie 
// Initialisations des sorties	
	LED = LED_Off;
	Flag_BCL = 0;
  Flag_T2 = 0;
	Flag_T4 = 0;
	SIG_OUT = 0;

//Config Timer 2 en Auto-reload toutes les 5ms
	Config_Timer2();
//Config Timer 4 en compteur d'évènements	
	Config_Timer4();
// Validation globale des interruptions	
	EA = 1;	
	
// Boucle infinie	
   while (1)
   {  
      Flag_BCL = 1;
		  Flag_BCL = 0;
//		  LED = ~LED;
//     fct_tempo(50000);		  
   }
}
//------------------------------------------------------------------------------------
// Config_Timer2
//------------------------------------------------------------------------------------
void Config_Timer2(void)
{
// Configurer T2CON CKCON RCAP2L RCAP2H TL2 et TH2
   CKCON &= 0xdf;         // T2M: Timer 2 Clock Select
                          // CLK = sysclk/12
   TF2= 0;		            // RAZ Flag TF2 Overflow Timer2
   EXF2 = 0;              // RAZ Flag EXF2
   EXEN2 = 0;	            // Action entrée T2EX dévalidée
   CT2 = 0;               // Mode Timer
   CPRL2 = 0;             // Auto reload of timer 2
                          // On a utilisé l’écriture Bit à bit sur T2CON
  

   RCAP2 = -(((SYSCLK/12)/200)); //RCAP2 déclaré en SFR16 5ms = 200Hz
   T2 = RCAP2;       // pour un premier cycle de bonne durée
   TR2 = 1;          // Timer2 démarré
   PT2 = 1;	         //INT Timer2 priorité haute
   ET2 = 1;	         // INT Timer2 autorisée
	
}
//------------------------------------------------------------------------------------
// Config_Timer4
//------------------------------------------------------------------------------------
void Config_Timer4(void)
{
// Configurer T4CON CKCON RCAP4L RCAP4H TL4 et TH4
  T4CON &= ~(1<<2);	//TR4 = 0 -- Timer stoppé pour configurer 
	T4CON |= (1<<1);  // C/T4 = 1 -- Mode Compteur
	                  // Entrée CLK sur T4
	 
   T4CON &= ~(1<<7);	// RAZ Flag TF4 Overflow Timer2
   T4CON &= ~(1<<6);	// RAZ Flag EXF4
	 T4CON &= ~(1<<0);	// CP/RL4 = 0 -- Mode Autorechargement
   T4CON &= ~(1<<3);	// EXEN4 = 0 -- Action entrée T4EX dévalidée
  
  

   RCAP4 = 65536-50;  // Tous les 50 évènements, on change l'étatde SIG_OUT
   T2 = RCAP2;          // pour un premier cycle de bonne durée
   T4CON |= (1<<2);	 //TR4 = 1 -- Timer4 démarré 
	
   EIP2 |= (1<<2); //PT4=1 -- Int Timer4 priorité haute
   EIE2 |= (1<<2); // ET4=1 -- Interruption T4 autorisée
	
}
//------------------------------------------------------------------------------------
// ISR_Timer2
//------------------------------------------------------------------------------------
void ISR_Timer2(void) interrupt 5
{
	static unsigned char	CP_Bcl_5ms;
	Flag_T2 = 1;
  if (TF2)
  {		
	   TF2= 0;		// RAZ Flag TF2 Overflow Timer2
	   CP_Bcl_5ms++;
	   if (CP_Bcl_5ms >= 10) 
		 {
				CP_Bcl_5ms = 0;
				LED = ~LED;
			}
		}	
  if (EXF2) EXF2=0; // Sécurité si INT EXF2
  		
  Flag_T2 = 0;
	
}
/------------------------------------------------------------------------------------
// ISR_Timer2
//------------------------------------------------------------------------------------
void ISR_Timer4(void) interrupt 16
{
	//static unsigned char	CP_Bcl_5ms;
	Flag_T4 = 1;
  if (T4CON&(1<<7))
  {		
	   T4CON &= ~(1<<7);		// RAZ Flag TF4 Overflow Timer4
	   SIG_OUT = ~SIG_OUT;
		}		 
	 if (T4CON&(1<<6))  T4CON &= ~(1<<6);  // Sécurité si INT EXF4
  Flag_T4 = 0;
	
}
/******************************************************************************/
/*                                                                            */
/*              Ostfalia Hochschule für angewandte Wissenschaften             */
/*                        Fakultät für Fahrzeugtechnik                        */
/*           Institut für Fahrzeuginformatik und Fahrzeugelektronik           */
/*                             Fahrzeuginformatik                             */
/*                                                                            */
/* Paket:        MPT_LAB                                                      */
/*                                                                            */
/* Modul:        MPT_LAB_1                                                    */
/*                                                                            */
/* Beschreibung: Aufgaben 1.MPT-Labor                                         */
/*                                                                            */
/* Funktionen:   A_1_1: Einfache digitale Portausgabe (LED)                   */
/*                                                                            */
/* Version:      1.0 / 120716 / V. v. Holt                                    */
/*                                                                            */
/******************************************************************************/

//------------------------------------------------------------------------------
//  Headerdateien
//------------------------------------------------------------------------------
// Allgemeine Headerdateien
#include <avr/io.h>

// Eigene Headerdateien
#include "MPT_LAB_MAIN.h"



#ifndef ENABLE_LSG
#ifdef ENABLE_A_1
#ifdef ENABLE_A_1_1
//------------------------------------------------------------------------------
//  Makro-/Konstantendefinitionen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Private Variablen
//------------------------------------------------------------------------------
	
	
//------------------------------------------------------------------------------
//  Interrupt Service Routinen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Private Funktionen
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Aufgabe A_1_1: Einfache digitale Portausgabe (LED)
// A_1_1_1: Erste LED (LED_0) einschalten.
// A_1_1_2: Jede zweite LED (LED_0, LED_2, LED_4, LED_6) einschalten.
//------------------------------------------------------------------------------

//##############################################################################

// A_1_1_1: Erste LED (LED_0) einschalten.
void A_1_1_1(void)
{
	// Datenrichtungsregister von Port C einstellen
	// Datenrichtungsbit = '1' => Ausgang
	// Datenrichtungsbit = '0' => Eingang 
	// Datenrichtungsbits 7-1: Eingang
	// Datenrichtungsbit    0: Ausgang
	DDRC = 0b00000001;

	// Portausgangsbits von Port C setzen
	// LED an Portbit 0 soll eingeschaltet werden.
	// Da die LEDs an den Portausgängen als logisch negativ verschaltet sind,
	// muss zur Aktivierung einer LED der Ausgang invers gesetzt werden, d.h. logisch '0'.
	// Portbit  0:   '0' setzen => LED ein.
	// Portbits 7-1: kein Einfluss, da als Eingang geschaltet (s.o. DDRC)
	PORTC = ~(0b00000001);  // = PORTC = 0b11111110
	
	while (1)
	{
	}		
}	

//##############################################################################

// A_1_1_2: Jede zweite LED (LED_0, LED_2, LED_4, LED_6) einschalten.
void A_1_1_2(void)
{
	// Datenrichtungsregister von Port C einstellen:
	// Datenrichtungsbit = '1' => Ausgang
	// Datenrichtungsbit = '0' => Eingang 
	// Datenrichtungsbits 7,5,3,1: Eingang
	// Datenrichtungsbits 6,4,2,0: Ausgang
  // IHR_CODE_HIER ...
  
	DDRC = 0b01010101;

	// Portausgangsbits von Port C setzen
	// LEDs an Portbits 0,2,4,6 sollen eingeschaltet werden.
	// Da die LEDs an den Portausgängen als logisch negativ verschaltet sind,
	// muss zur Aktivierung einer LED der Ausgang invers gesetzt werden, d.h. logisch '0'.
	// Portbits 0,2,4,6:   '0' setzen => LEDs ein.
	// Portbits 7,5,3,1: kein Einfluss, da als Eingang geschaltet (s.o. DDRC)
  // IHR_CODE_HIER ...
  
	PORTC = 0x00;
	
	while(1)
	{
	}
}	

//##############################################################################

#endif /* ENABLE_A_1_1 */
#endif /* ENABLE_A_1 */
#endif /* ENABLE_LSG */

/*
 *  EoF
 */

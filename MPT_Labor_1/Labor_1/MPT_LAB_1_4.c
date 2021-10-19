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
/* Funktionen:   A_1_4: Einfache digitale Porteingabe (Taster)                */
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
#ifdef ENABLE_A_1_4
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
// Aufgabe A_1_4: Einfache digitale Porteingabe (Taster)
// A_1_4_1: Abfrage von Port B (Taster) und 1:1-Ausgabe auf Port C (LED)
//------------------------------------------------------------------------------

//##############################################################################

// A_1_4_1: Abfrage von Port B (Taster) und 1:1-Ausgabe auf Port C (LED)
void A_1_4_1(void)
{
  // Datenrichtungsregister als Ein-/Ausgang konfigurieren:
	// Portbit = '1' => Ausgang
	// Portbit = '0' => Eingang 
	// DDRC für LED-Ansteuerung als Ausgang setzen.
	DDRC = 0b11111111;
	// DDRB für Taster-Einlesen als Eingang setzen.
	DDRB = 0b00000000;

	while (1)
	{
		// Wir lesen das Eingangsregister von Port B, PINB (Port INput B), ein
		// und geben es direkt invertiert (invertierter LED-Aktivpegel) auf den 
		// LEDs am Ausgaberegister des Port C, PORTC, aus.
		PORTC = ~PINB;
	}		
}

//##############################################################################

#endif /* ENABLE_A_1_4 */
#endif /* ENABLE_A_1 */
#endif /* ENABLE_LSG */

/*
 *  EoF
 */

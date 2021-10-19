/*
 * MPT.c
 *
 * Created: 25.05.2012 18:12:01
 *  Author: holtv
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "MPT_LAB_MAIN.h"
#include "Labor_1/MPT_Lab_1.h"


int main(void)
{
	//##############################################################################
	//
	// Aufgabe A_1
	//
	//##############################################################################
  //------------------------------------------------------------------------------
  // Aufgabe A_1_1: Einfache digitale Portausgabe (LED)
  // A_1_1_1: Erste LED (LED_0) einschalten.
  // A_1_1_2: Jede zweite LED (LED_0, LED_2, LED_4, LED_6) einschalten.
  //------------------------------------------------------------------------------
  //A_1_1_1();
  //A_1_1_2();

  //------------------------------------------------------------------------------
  // Aufgabe A_1_2: LED-Blinken
  // A_1_2_1: LED-Blinken ohne Verz�gerung
  // A_1_2_2: LED-Blinken mit einfacher Verz�gerungsschleife
  // A_1_2_3: LED-Blinken mit ausgetesteter ("kalibrierter") Verz�gerungsschleife
  // A_1_2_4: Auslagerung einer "normierten" Verz�gerungsschleife in Funktion
  //------------------------------------------------------------------------------
  //A_1_2_1();
  //A_1_2_2();
  //A_1_2_3();
  //A_1_2_4();

  //------------------------------------------------------------------------------
  // Aufgabe A_1_3: LED-Lauflicht
  // Aufgabe A_1_3_1: Lauflicht L-R-L-... "Knightrider"
  //------------------------------------------------------------------------------
  //A_1_3_1();

  //------------------------------------------------------------------------------
  // Aufgabe A_1_4: Einfache digitale Porteingabe (Taster)
  // A_1_4_1: Abfrage von Port B (Taster) und 1:1-Ausgabe auf Port C (LED)
  //------------------------------------------------------------------------------
  //A_1_4_1();

  //------------------------------------------------------------------------------
  // Aufgabe A_1_5: Z�hler
  // A_1_5_1: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED
  // A_1_5_2: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
  //          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
  //          werden f�r weiteres Inkrementieren.
  // A_1_5_3: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
  //          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
  //          werden f�r weiteres Inkrementieren.
  //          Wie Aufgabe A_1_5_2 nur mit 'switch-case' statt 'if-else'.
  // A_1_5_4: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
  //          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
  //          werden f�r weiteres Inkrementieren.
  //          Wie Aufgabe A_1_5_3 mit Tastenentprellen �ber 'Wait_x_ms'.
  // A_1_5_5: Vorw�rts-/R�ckw�rtsz�hler �ber Taster an PB7 und PB6 mit Ausgabe des Z�hlerstands auf LED.
  //          Zustandsautomat erfordert Loslassen der Tasten vor erneuter Bet�tigung und verhindert,
  //          das mehrere Tasten gleichzeitig gedr�ckt werden.
  //------------------------------------------------------------------------------
  //A_1_5_1();
  //A_1_5_2();
  //A_1_5_3();
  //A_1_5_4();
  A_1_5_5();




  while(1)
  {
      // Wir machen nichts (mehr)...
  }
}


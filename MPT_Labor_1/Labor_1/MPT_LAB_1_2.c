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
/* Funktionen:   A_1_2: LED-Blinken                                           */
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
#ifdef ENABLE_A_1_2
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
void A_1_2_Wait_x_ms(uint16_t x_ms)
{
  // IHR_CODE_HIER ...
  const uint16_t loopTime1 = 726;
  
  uint16_t i_w1;
  
  for(uint16_t i = 0; i < x_ms; i++){
	  for (i_w1 = 0; i_w1 < loopTime1; i_w1++)
	  {
	  }
  }
}


//------------------------------------------------------------------------------
//  Public Funktionen
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Aufgabe A_1_2: LED-Blinken
// A_1_2_1: LED-Blinken ohne Verzögerung
// A_1_2_2: LED-Blinken mit einfacher Verzögerungsschleife
// A_1_2_3: LED-Blinken mit ausgetesteter ("kalibrierter") Verzögerungsschleife
// A_1_2_4: Auslagerung einer "normierten" Verzögerungsschleife in Funktion
//------------------------------------------------------------------------------

//##############################################################################

// A_1_2_1: LED-Blinken ohne Verzögerung
void A_1_2_1(void)
{
	// Datenrichtungsregister von Port C einstellen:
	// Datenrichtungsbit = '1' => Ausgang
	// Datenrichtungsbit = '0' => Eingang 
	// Datenrichtungsbits 7,5,3,1: Eingang
	// Datenrichtungsbits 6,4,2,0: Ausgang
  // IHR_CODE_HIER ...
  
	DDRC = 0b01010101;

	while (1)
	{
	  // Portausgangsbits von Port C setzen
	  // LEDs an Portbits 0,2,4,6 sollen eingeschaltet werden.
	  // Da die LEDs an den Portausgängen als logisch negativ verschaltet sind,
	  // muss zur Aktivierung einer LED der Ausgang invers gesetzt werden, d.h. logisch '0'.
	  // Portbits  0,2,4,6:   '0' setzen => LEDs ein.
	  // Portbits 7,5,3,1: kein Einfluss, da als Eingang geschaltet (s.o. DDRC)
    // IHR_CODE_HIER ...
	
		PORTC = 0x00;

	  // Portausgangsbits von Port C setzen.
	  // LEDs an Portbits 0,2,4,6 sollen ausgeschaltet werden.
	  // Da die LEDs an den Portausgängen als logisch negativ verschaltet sind,
	  // muss zur Deaktivierung einer LED der Ausgang invers gesetzt werden, d.h. logisch '1'.
	  // Portbits  0,2,4,6:   '1' setzen => LEDs aus.
	  // Portbits 7,5,3,1: kein Einfluss, da als Eingang geschaltet (s.o. DDRC)
    // IHR_CODE_HIER ...
	
		PORTC = 0xff;
	}		
}

//##############################################################################

// A_1_2_2: LED-Blinken mit einfacher Verzögerungsschleife
void A_1_2_2(void)
{
  // IHR_CODE_HIER ...
  
  //Initialsieren der Leseschreibrichtung
  DDRC = 0b01010101;
  
  //LoopTime init
  //const uint16_t loopTime = 12500; //half period
  const uint16_t loopTime = 6250; //full period
  
  while (1)
  {
	  //Anschalten
	  PORTC = 0x00;
	  
	  //Busy-Waiting
	  for(uint16_t i = 0; i < loopTime; i++){
	  }
	  
	  //Ausschalten
	  PORTC = 0xff;
	  
	  //Busy-Waiting
	  for(uint16_t i = 0; i < loopTime; i++){
	  }
  }
  
}

//##############################################################################

// A_1_2_3: LED-Blinken mit ausgetesteter ("kalibrierter") Verzögerungsschleife
void A_1_2_3(void)
{
  // IHR_CODE_HIER ...
  
  //Initialsieren der Leseschreibrichtung
  DDRC = 0b01010101;
  
  //LoopTime init
  const uint32_t loopTime1 = 667; 
  const uint32_t loopTime2 = 1709; 
  
  while (1)
  {
	  //Anschalten
	  PORTC = 0x00;
	  
	  //Busy-Waiting
	  for(uint32_t i = 0; i < loopTime1; i++){
			for(uint32_t i = 0; i < loopTime2; i++){
			}
	  }
	  
	  //Ausschalten
	  PORTC = 0xff;
	  
	  //Busy-Waiting
	  for(uint32_t i = 0; i < loopTime1; i++){
			for(uint32_t i = 0; i < loopTime2; i++){
			}
	  }
  }
}

//##############################################################################
// A_1_2_4: Auslagerung einer "normierten" Verzögerungsschleife in Funktion
void A_1_2_4(void)
{
	// IHR_CODE_HIER ...
  
	//Initialsieren der Leseschreibrichtung
	DDRC = 0b01010101;
  
	// Verwenden Sie eine auf 1 ms "normierten" Verzögerungsschleife, der Sie die gewünschte Wartezeit als Parameter übergeben! Den Funktionsrohbau hierzu finden Sie oben unter "Private Funktionen": "A_1_2_Wait_x_ms()".
	while(1){
		PORTC = 0x00;
		A_1_2_Wait_x_ms(500);
		PORTC = 0xff;
		A_1_2_Wait_x_ms(500);
	}
}
//##############################################################################

#endif /* ENABLE_A_1_2 */
#endif /* ENABLE_A_1 */
#endif /* ENABLE_LSG */

/*
 *  EoF
 */

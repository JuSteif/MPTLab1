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
/* Funktionen:   A_1_5: Zähler                                                */
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
#ifdef ENABLE_A_1_5
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
void A_1_5_Wait_x_ms(uint16_t x_ms)
{
  // IHR_CODE_HIER ... => A_1_2
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
// Aufgabe A_1_5: Zähler
// A_1_5_1: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED
// A_1_5_2: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
// A_1_5_3: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_2 nur mit 'switch-case' statt 'if-else'.
// A_1_5_4: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_3 mit Tastenentprellen über 'Wait_x_ms'.
// A_1_5_5: Vorwärts-/Rückwärtszähler über Taster an PB7 und PB6 mit Ausgabe des Zählerstands auf LED.
//          Zustandsautomat erfordert Loslassen der Tasten vor erneuter Betätigung und verhindert,
//          das mehrere Tasten gleichzeitig gedrückt werden.
//------------------------------------------------------------------------------

//##############################################################################

// A_1_5_1: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED
//          Problem: Tastenprellen und hohe Wiederholrate
void A_1_5_1(void)
{
	// 8-Bit-Variable für den Zähler
	uint8_t Cnt = 0;
  	
  // Richtungsbits für LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits für Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Zählerstand = 0 ausgeben.
  // Invertierung des Zählerstands für die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
    // Abfrage des Taster an PB7
	  // Durch (1<<7) erzeugen wir eine Bitmaske, bei der nur das Bit 7 = 1 ist, alle anderen
	  // Bits sind 0.
	  // Diese Bitmaske verknüpfen wir per bitweisem UND mit dem Eingangsregister von Port B, PINB.
	  // Das Ergebnis der UND-Verknüpfung ist nur dann != 0, wenn auch in PINB das Bit 7 = 1 war, d.h.
	  // die Taste gedrückt war. Sonst ist das Ergebnis = 0.
	  // In "C" gilt eine Bedingung wie bei "if (Bedingung)" immer dann als erfüllt, wenn der Wert
	  // der Bedingung != 0 ist, egal ob die Bedingung den Wert 1, 2 oder 12345 oder .... ergibt.
	  // Nur wenn eine Bedingung den Wert 0 ergibt, gilt sie als nicht erfüllt.
		if ((PINB & (1 << 7)))
		{
			// Zähler um 1 erhöhen
  			Cnt = Cnt + 1;

			// Neuen Zählerstand auf den LEDs ausgeben
			PORTC = ~Cnt;
		}
	}		
}	

//##############################################################################

// A_1_5_2: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
void A_1_5_2(void)
{
	// 8-Bit-Variable für den Zähler
	uint8_t Cnt = 0;
  // Zustandsvariable: 1=Taste gedrückt 0=Taste nicht gedrückt
  uint8_t State = 0;
  	
  // Richtungsbits für LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits für Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Zählerstand = 0 ausgeben.
  // Invertierung des Zählerstands für die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
      // Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedrückt
	  // Zusätzlich Überprüfung in welchem Zustand wir sind:
	  // State == 0 => Taste war nicht gedrückt => Bedingung erfüllt => Zähler inkrementieren + Zustandswechsel 0 => 1
	  // State == 1 => Taste war schon gedrückt => Bedingung nicht erfüllt => Überspringen
		if ((PINB & (1 << 7)) && (State == 0))
		{
			// Zähler um 1 erhöhen
  			Cnt = Cnt + 1;

			// Zustandswechsel 0 => 1: Taste gedrückt
			State = 1;

			// Neuen Zählerstand auf den LEDs ausgeben
			PORTC = ~Cnt;
		}
		// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedrückt
		// Zusätzlich Überprüfung in welchem Zustand wir sind:
		// State == 0 => Taste war nicht gedrückt => Bedingung nicht erfüllt => Überspringen
		// State == 1 => Taste war schon gedrückt => Bedingung erfüllt => Zustandswechsel 1 => 0
		else if (!(PINB & (1 << 7)) && (State == 1))
		{
			// Zustandswechsel 1 => 0: Taste nicht (mehr) gedrückt
			State = 0;
		}			
	}		
}	

//##############################################################################

// A_1_5_3: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_2 nur mit 'switch-case' statt 'if-else'.
void A_1_5_3(void)
{
  // 8-Bit-Variable für den Zähler
  uint8_t Cnt = 0;
  // Zustandsvariable: 1=Taste gedrückt 0=Taste nicht gedrückt
  uint8_t State = 0;
  	
  // Richtungsbits für LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits für Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Zählerstand = 0 ausgeben.
  // Invertierung des Zählerstands für die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
		// Schalter in welchem Zustand das Programm ist.
		switch (State)
		{
			// State == 0 => Diesen Programmabschnitt ausführen
			case 0:
				// Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedrückt
				// Überprüfung des Zustands wie in A_1_5_2 entfällt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
				if (PINB & (1 << 7))
				{
					// Zähler um 1 erhöhen
  					Cnt = Cnt + 1;

					// Zustandswechsel 0 => 1: Taste gedrückt
					State = 1;

					// Neuen Zählerstand auf den LEDs ausgeben
					PORTC = ~Cnt;
				}
				else
				{
					// Nur über den "Leer"-Übergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
					// Lässt man "normalerweise" weg.
				}				  
				break;
			
				// State == 1 => Diesen Programmabschnitt ausführen
			case 1:
				// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedrückt
				// Überprüfung des Zustands wie in A_1_5_2 entfällt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
    			if (!(PINB & (1 << 7)))
				{
				// Zustandswechsel 1 => 0: Taste nicht (mehr) gedrückt
					State = 0;
				}
				else
				{
					// Nur über den "Leer"-Übergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
					// Lässt man "normalerweise" weg.
				}				  			
				break; 
			// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
			default:
				break;
		}		
	}		
}	

//##############################################################################

// A_1_5_4: Vorwärtszähler über Taster an PB7 mit Ausgabe des Zählerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut betätigt
//          werden für weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_3 mit Tastenentprellen über 'Wait_x_ms'.
void A_1_5_4(void)
{
	// 8-Bit-Variable für den Zähler
	uint8_t Cnt = 0;
	// Zustandsvariable: 1=Taste gedrückt 0=Taste nicht gedrückt
	uint8_t State = 0;
  	
	// Richtungsbits für LEDs auf Ausgang
	DDRC = 0b11111111;
	// Richtungsbits für Taster auf Eingang
	DDRB = 0b00000000;

	// Initialen Zählerstand = 0 ausgeben.
	// Invertierung des Zählerstands für die Ausgabe auf den LEDs 
	// nicht vergessen.
	PORTC = ~Cnt;
  
	while (1)
	{
		// Schalter in welchem Zustand das Programm ist.
		switch (State)
		{
			// State == 0 => Diesen Programmabschnitt ausführen
			case 0:
				// Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedrückt
				// Überprüfung des Zustands wie in A_1_5_2 entfällt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
				if (PINB & (1 << 7))
				{
					// Zähler um 1 erhöhen
  					Cnt = Cnt + 1;

					// Zustandswechsel 0 => 1: Taste gedrückt
					State = 1;

					// Neuen Zählerstand auf den LEDs ausgeben
					PORTC = ~Cnt;
		  
					// Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
					A_1_5_Wait_x_ms(50);
				}
				else
				{
					// Nur über den "Leer"-Übergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
					// Lässt man "normalerweise" weg.
				}				  
				break;
			
				// State == 1 => Diesen Programmabschnitt ausführen
			case 1:
				// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedrückt
				// Überprüfung des Zustands wie in A_1_5_2 entfällt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls wären wir gar nicht an dieser Stelle.
    			if (!(PINB & (1 << 7)))
				{
					// Zustandswechsel 1 => 0: Taste nicht (mehr) gedrückt
					State = 0;

					// Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
					A_1_5_Wait_x_ms(50);
				}
				else
				{
					// Nur über den "Leer"-Übergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
					// Lässt man "normalerweise" weg.
				}				  			
				break;
			  
				// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
			default:
				break;
		}		
	}		
}	

//##############################################################################

// A_1_5_5: Vorwärts-/Rückwärtszähler über Taster an PB7 und PB6 mit Ausgabe des Zählerstands auf LED.
//          Zustandsautomat erfordert Loslassen der Tasten vor erneuter Betätigung und verhindert,
//          das mehrere Tasten gleichzeitig gedrückt werden.
void A_1_5_5(void)
{
  // IHR_CODE_HIER ...
  const int wait = 1;
  
  // 8-Bit-Variable für den Zähler
  uint8_t Cnt = 0;
  // Zustandsvariable: 0 = Nichts gedrückt, 1 = Taste-Up, 2 = Taste-Down, 3 = Taste-Up-and-Down 
  uint8_t State = 0;
  
  // Richtungsbits
  DDRC = 0b11111111;
  DDRB = 0b00000000;

  //LED´s auf 0 setzen
  PORTC = ~Cnt;
  
  while (1)
  {
	  switch (State)
	  {
		  case 0:
				if (PINB & (1 << 6) && PINB & (1 << 7)) // Beide Tasten gedrückt aus State nichts
				{
					State = 3;
			  
					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && !(PINB & (1 << 7))) // Taste-Down gedrückt aus State nichts
				{
					if(Cnt > 0){
						Cnt--;
					}

					State = 2;

					PORTC = ~Cnt;
					
					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 7) && !(PINB & (1 << 6))) // Taste-Up gedrückt aus State nichts
				{
					if(Cnt < 255){
						Cnt++;
					}

					State = 1;

					PORTC = ~Cnt;
					
					A_1_5_Wait_x_ms(wait);
				}
				break;
		  case 1:
				if (!(PINB & (1 << 7)) && !(PINB & (1 << 6)))
				{
					State = 0;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && PINB & (1 << 7))
				{
					State = 3;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && !(PINB & (1 << 7)))
				{
					State = 2;

					A_1_5_Wait_x_ms(wait);
				}
				break;
		case 2:
				if (!(PINB & (1 << 7)) && !(PINB & (1 << 6)))
				{
					State = 0;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && PINB & (1 << 7))
				{
					State = 3;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 7) && !(PINB & (1 << 6)))
				{
					State = 1;

					A_1_5_Wait_x_ms(wait);
				}
				break;
		case 3:
				if (!(PINB & (1 << 7)) && !(PINB & (1 << 6)))
				{
					State = 0;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && !(PINB & (1 << 7)))
				{
					State = 2;

					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 7) && !(PINB & (1 << 6)))
				{
					State = 1;

					A_1_5_Wait_x_ms(wait);
				}
				break;
		  
		  // Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
		  default:
				break;
	  }
  }
}	

//##############################################################################



#endif /* ENABLE_A_1_5 */
#endif /* ENABLE_A_1 */
#endif /* ENABLE_LSG */

/*
 *  EoF
 */

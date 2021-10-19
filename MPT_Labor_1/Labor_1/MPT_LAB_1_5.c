/******************************************************************************/
/*                                                                            */
/*              Ostfalia Hochschule f�r angewandte Wissenschaften             */
/*                        Fakult�t f�r Fahrzeugtechnik                        */
/*           Institut f�r Fahrzeuginformatik und Fahrzeugelektronik           */
/*                             Fahrzeuginformatik                             */
/*                                                                            */
/* Paket:        MPT_LAB                                                      */
/*                                                                            */
/* Modul:        MPT_LAB_1                                                    */
/*                                                                            */
/* Beschreibung: Aufgaben 1.MPT-Labor                                         */
/*                                                                            */
/* Funktionen:   A_1_5: Z�hler                                                */
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

//##############################################################################

// A_1_5_1: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED
//          Problem: Tastenprellen und hohe Wiederholrate
void A_1_5_1(void)
{
	// 8-Bit-Variable f�r den Z�hler
	uint8_t Cnt = 0;
  	
  // Richtungsbits f�r LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits f�r Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Z�hlerstand = 0 ausgeben.
  // Invertierung des Z�hlerstands f�r die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
    // Abfrage des Taster an PB7
	  // Durch (1<<7) erzeugen wir eine Bitmaske, bei der nur das Bit 7 = 1 ist, alle anderen
	  // Bits sind 0.
	  // Diese Bitmaske verkn�pfen wir per bitweisem UND mit dem Eingangsregister von Port B, PINB.
	  // Das Ergebnis der UND-Verkn�pfung ist nur dann != 0, wenn auch in PINB das Bit 7 = 1 war, d.h.
	  // die Taste gedr�ckt war. Sonst ist das Ergebnis = 0.
	  // In "C" gilt eine Bedingung wie bei "if (Bedingung)" immer dann als erf�llt, wenn der Wert
	  // der Bedingung != 0 ist, egal ob die Bedingung den Wert 1, 2 oder 12345 oder .... ergibt.
	  // Nur wenn eine Bedingung den Wert 0 ergibt, gilt sie als nicht erf�llt.
		if ((PINB & (1 << 7)))
		{
			// Z�hler um 1 erh�hen
  			Cnt = Cnt + 1;

			// Neuen Z�hlerstand auf den LEDs ausgeben
			PORTC = ~Cnt;
		}
	}		
}	

//##############################################################################

// A_1_5_2: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
//          werden f�r weiteres Inkrementieren.
void A_1_5_2(void)
{
	// 8-Bit-Variable f�r den Z�hler
	uint8_t Cnt = 0;
  // Zustandsvariable: 1=Taste gedr�ckt 0=Taste nicht gedr�ckt
  uint8_t State = 0;
  	
  // Richtungsbits f�r LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits f�r Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Z�hlerstand = 0 ausgeben.
  // Invertierung des Z�hlerstands f�r die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
      // Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedr�ckt
	  // Zus�tzlich �berpr�fung in welchem Zustand wir sind:
	  // State == 0 => Taste war nicht gedr�ckt => Bedingung erf�llt => Z�hler inkrementieren + Zustandswechsel 0 => 1
	  // State == 1 => Taste war schon gedr�ckt => Bedingung nicht erf�llt => �berspringen
		if ((PINB & (1 << 7)) && (State == 0))
		{
			// Z�hler um 1 erh�hen
  			Cnt = Cnt + 1;

			// Zustandswechsel 0 => 1: Taste gedr�ckt
			State = 1;

			// Neuen Z�hlerstand auf den LEDs ausgeben
			PORTC = ~Cnt;
		}
		// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedr�ckt
		// Zus�tzlich �berpr�fung in welchem Zustand wir sind:
		// State == 0 => Taste war nicht gedr�ckt => Bedingung nicht erf�llt => �berspringen
		// State == 1 => Taste war schon gedr�ckt => Bedingung erf�llt => Zustandswechsel 1 => 0
		else if (!(PINB & (1 << 7)) && (State == 1))
		{
			// Zustandswechsel 1 => 0: Taste nicht (mehr) gedr�ckt
			State = 0;
		}			
	}		
}	

//##############################################################################

// A_1_5_3: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
//          werden f�r weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_2 nur mit 'switch-case' statt 'if-else'.
void A_1_5_3(void)
{
  // 8-Bit-Variable f�r den Z�hler
  uint8_t Cnt = 0;
  // Zustandsvariable: 1=Taste gedr�ckt 0=Taste nicht gedr�ckt
  uint8_t State = 0;
  	
  // Richtungsbits f�r LEDs auf Ausgang
	DDRC = 0b11111111;
  // Richtungsbits f�r Taster auf Eingang
	DDRB = 0b00000000;

  // Initialen Z�hlerstand = 0 ausgeben.
  // Invertierung des Z�hlerstands f�r die Ausgabe auf den LEDs 
  // nicht vergessen.
  PORTC = ~Cnt;
  
	while (1)
	{
		// Schalter in welchem Zustand das Programm ist.
		switch (State)
		{
			// State == 0 => Diesen Programmabschnitt ausf�hren
			case 0:
				// Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedr�ckt
				// �berpr�fung des Zustands wie in A_1_5_2 entf�llt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls w�ren wir gar nicht an dieser Stelle.
				if (PINB & (1 << 7))
				{
					// Z�hler um 1 erh�hen
  					Cnt = Cnt + 1;

					// Zustandswechsel 0 => 1: Taste gedr�ckt
					State = 1;

					// Neuen Z�hlerstand auf den LEDs ausgeben
					PORTC = ~Cnt;
				}
				else
				{
					// Nur �ber den "Leer"-�bergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
					// L�sst man "normalerweise" weg.
				}				  
				break;
			
				// State == 1 => Diesen Programmabschnitt ausf�hren
			case 1:
				// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedr�ckt
				// �berpr�fung des Zustands wie in A_1_5_2 entf�llt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls w�ren wir gar nicht an dieser Stelle.
    			if (!(PINB & (1 << 7)))
				{
				// Zustandswechsel 1 => 0: Taste nicht (mehr) gedr�ckt
					State = 0;
				}
				else
				{
					// Nur �ber den "Leer"-�bergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
					// L�sst man "normalerweise" weg.
				}				  			
				break; 
			// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
			default:
				break;
		}		
	}		
}	

//##############################################################################

// A_1_5_4: Vorw�rtsz�hler �ber Taster an PB7 mit Ausgabe des Z�hlerstands auf LED.
//          Merken des Tastenzustands => Taste muss erst losgelassen und erneut bet�tigt
//          werden f�r weiteres Inkrementieren.
//          Wie Aufgabe A_1_5_3 mit Tastenentprellen �ber 'Wait_x_ms'.
void A_1_5_4(void)
{
	// 8-Bit-Variable f�r den Z�hler
	uint8_t Cnt = 0;
	// Zustandsvariable: 1=Taste gedr�ckt 0=Taste nicht gedr�ckt
	uint8_t State = 0;
  	
	// Richtungsbits f�r LEDs auf Ausgang
	DDRC = 0b11111111;
	// Richtungsbits f�r Taster auf Eingang
	DDRB = 0b00000000;

	// Initialen Z�hlerstand = 0 ausgeben.
	// Invertierung des Z�hlerstands f�r die Ausgabe auf den LEDs 
	// nicht vergessen.
	PORTC = ~Cnt;
  
	while (1)
	{
		// Schalter in welchem Zustand das Programm ist.
		switch (State)
		{
			// State == 0 => Diesen Programmabschnitt ausf�hren
			case 0:
				// Abfrage ob Bit 7 an PINB == 1, d.h. Taste gedr�ckt
				// �berpr�fung des Zustands wie in A_1_5_2 entf�llt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls w�ren wir gar nicht an dieser Stelle.
				if (PINB & (1 << 7))
				{
					// Z�hler um 1 erh�hen
  					Cnt = Cnt + 1;

					// Zustandswechsel 0 => 1: Taste gedr�ckt
					State = 1;

					// Neuen Z�hlerstand auf den LEDs ausgeben
					PORTC = ~Cnt;
		  
					// Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
					A_1_5_Wait_x_ms(50);
				}
				else
				{
					// Nur �ber den "Leer"-�bergang 0=>0 aus dem Zustandsdiagramm zu veranschaulichen.
					// L�sst man "normalerweise" weg.
				}				  
				break;
			
				// State == 1 => Diesen Programmabschnitt ausf�hren
			case 1:
				// Abfrage ob Bit 7 an PINB == 0, d.h. Taste nicht gedr�ckt
				// �berpr�fung des Zustands wie in A_1_5_2 entf�llt, das erledigt schon die
				// "switch-case"-Anweisung, d.h. andernfalls w�ren wir gar nicht an dieser Stelle.
    			if (!(PINB & (1 << 7)))
				{
					// Zustandswechsel 1 => 0: Taste nicht (mehr) gedr�ckt
					State = 0;

					// Erst einmal das Tastenprellen abwarten ehe wir weitermachen...
					A_1_5_Wait_x_ms(50);
				}
				else
				{
					// Nur �ber den "Leer"-�bergang 1=>1 aus dem Zustandsdiagramm zu veranschaulichen.
					// L�sst man "normalerweise" weg.
				}				  			
				break;
			  
				// Default: Wenn ((State != 0) && (State != 1)) => Fehler: Fall darf bei korrektem Programm nicht auftreten.
			default:
				break;
		}		
	}		
}	

//##############################################################################

// A_1_5_5: Vorw�rts-/R�ckw�rtsz�hler �ber Taster an PB7 und PB6 mit Ausgabe des Z�hlerstands auf LED.
//          Zustandsautomat erfordert Loslassen der Tasten vor erneuter Bet�tigung und verhindert,
//          das mehrere Tasten gleichzeitig gedr�ckt werden.
void A_1_5_5(void)
{
  // IHR_CODE_HIER ...
  const int wait = 1;
  
  // 8-Bit-Variable f�r den Z�hler
  uint8_t Cnt = 0;
  // Zustandsvariable: 0 = Nichts gedr�ckt, 1 = Taste-Up, 2 = Taste-Down, 3 = Taste-Up-and-Down 
  uint8_t State = 0;
  
  // Richtungsbits
  DDRC = 0b11111111;
  DDRB = 0b00000000;

  //LED�s auf 0 setzen
  PORTC = ~Cnt;
  
  while (1)
  {
	  switch (State)
	  {
		  case 0:
				if (PINB & (1 << 6) && PINB & (1 << 7)) // Beide Tasten gedr�ckt aus State nichts
				{
					State = 3;
			  
					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 6) && !(PINB & (1 << 7))) // Taste-Down gedr�ckt aus State nichts
				{
					if(Cnt > 0){
						Cnt--;
					}

					State = 2;

					PORTC = ~Cnt;
					
					A_1_5_Wait_x_ms(wait);
				}
				else if (PINB & (1 << 7) && !(PINB & (1 << 6))) // Taste-Up gedr�ckt aus State nichts
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

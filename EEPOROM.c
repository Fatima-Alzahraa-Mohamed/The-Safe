/*
 * EEPOROM.c
 *
 *
 *  Author: Zahraa Mohamed
 */ 
 #include <avr/io.h>
 #include "std_macros.h"
 
 void EEPROM_WRITE(unsigned short address ,unsigned char data)
 {
	 EEARL = address;
	 EEARH = address >>8;
	 EEDR = data;
	 SET_BIT(EECR,EEMWE);
	 SET_BIT(EECR,EEWE);
	 while( READ_BIT(EECR,EEWE)==1 );
 }
 
 unsigned char EEPROM_READ(unsigned short address)
 {
	 EEARL = address;
	 EEARH = address>>8;
	 SET_BIT(EECR,EERE);
	 return EEDR ;
 }
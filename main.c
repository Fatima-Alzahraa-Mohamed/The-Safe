/*
 * The Safe.c
 *
 * 
 * Author : Zahraa Mohamed
 */ 

#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "KEYPAD.h"
#include "LCD.h"
#include "EEPROM.h"

#define		EEPROM_STATUS_LOCATION		0x20
#define		EEPROM_PASSWORD_LOCATION1	0x21
#define		EEPROM_PASSWORD_LOCATION2	0x22
#define		EEPROM_PASSWORD_LOCATION3	0x23
#define		EEPROM_PASSWORD_LOCATION4	0x24
#define		MAX_TRIES					2

char arr[4];
int main(void)
{
	char value=NOTPRESSED;
	char flag=0,i;
	char tries=MAX_TRIES;
	KEYPAD_INIT();
	LCD_INIT();
	if (EEPROM_READ(EEPROM_STATUS_LOCATION)==NOTPRESSED)
	{
		LCD_SEND_STRING("set pass:");
		for (i=0;i<=3;i++)
		{
			do
			{
				value=KEYPAD_READ();
			}while (value==NOTPRESSED);
			LCD_SEND_CHAR(value);
			_delay_ms(500);
			LCD_MOVE_CURSOR(1,10+i);
			LCD_SEND_CHAR('*');
			_delay_ms(500);
			EEPROM_WRITE(EEPROM_PASSWORD_LOCATION1+i,value);
		}
		EEPROM_WRITE(EEPROM_STATUS_LOCATION,0x00);
	}
	while(flag==0)
	{
		arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;
		LCD_CLR_SCREEN();
		LCD_SEND_STRING("check pass:");
		for (i=0;i<=3;i++)
		{
			do
			{
				arr[i]=KEYPAD_READ();
			}while (arr[i]==NOTPRESSED);
			LCD_SEND_CHAR(arr[i]);
			_delay_ms(500);
			LCD_MOVE_CURSOR(1,12+i);
			LCD_SEND_CHAR('*');
			_delay_ms(500);
		}
		
		if(EEPROM_READ(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_READ(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_READ(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_READ(EEPROM_PASSWORD_LOCATION4)==arr[3])
		{
			LCD_CLR_SCREEN();
			LCD_SEND_STRING("right password");
			LCD_MOVE_CURSOR(2,1);
			LCD_SEND_STRING("safe opened");
			flag=1;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				LCD_CLR_SCREEN();
				LCD_SEND_STRING("wrong password");
				_delay_ms(1000);
				LCD_CLR_SCREEN();
				LCD_SEND_STRING("tries left:");
				LCD_SEND_CHAR(tries+48);
				_delay_ms(1000);
				
			}
			else
			{
				LCD_CLR_SCREEN();
				LCD_SEND_STRING("wrong password");
				LCD_MOVE_CURSOR(2,1);
				LCD_SEND_STRING("safe closed");
				flag=1;
			}
		}
	}
}


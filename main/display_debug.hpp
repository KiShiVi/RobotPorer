#ifndef DISPLAY_H
#define DISPLAY_H

/*
*  Класс для работы с виртуальным дисплеем
*
*/

#include "mem.hpp"

String utf8rus(String source);  //!< Функция для перевода строки на русский язык
String printPGM(byte idx);      //!< Функция для извлечения строки из flash памяти

class Display
{
	//!< Класс для работы с виртуальным дисплеем. Выводит информацию не на дисплей в Serial port
public:
	Display();                                        //!< Конструктор  
	void printRandToast();                            //!< Отображает случайный тост на дисплее
	void printInfo( uint16_t volume, uint8_t mode );  //!< Отображает информацию на дисплее - (volume - объем рюмки, mode - режим работы)
};

Display::Display()
{
	Serial.println(F("Display init"));
	Serial.println(F("Робот\nРазливайка"));
}

void Display::printRandToast()
{
	Serial.println( printPGM(random( 0, 20 ) ) );
}

void Display::printInfo( uint16_t volume, uint8_t mode )
{
	String res;
	res = volume;
	res += " ";
	
	if ( mode == 0 )
		res += "M";
	else if ( mode == 1 )
		res += "A";
	else if ( mode == 2 )
		res += "S";
	
	Serial.println( res );
}


void Display::printInfo( uint32_t volume )
{
	Serial.println( volume );
}


String utf8rus(String source)
{
	int i,k;
	String target;
	unsigned char n;
	char m[2] = { '0', '\0' };
	
	k = source.length(); i = 0;
	
	while (i < k) 
	{
		n = source[i]; i++;
		
		if (n >= 0xC0) 
		{
			switch (n) 
			{
			case 0xD0: 
			{
				n = source[i]; i++;
				if (n == 0x81) { n = 0xA8; break; }
				if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
				break;
			}
			case 0xD1: 
			{
				n = source[i]; i++;
				if (n == 0x91) { n = 0xB8; break; }
				if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
				break;
			}
			}
		}
		m[0] = n; target = target + String(m);
	}
	return target;
}

#endif

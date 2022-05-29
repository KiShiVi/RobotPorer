#ifndef DISPLAY_H
#define DISPLAY_H

/*
*  Класс для работы с дисплеем
*
*/

#include "mem.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

String utf8rus(String source);    //!< Функция для перевода строки на русский язык
String printPGM(byte idx);        //!< Функция для извлечения строки из flash памяти

class Display
{
	//!< Класс работы с дисплеем
public:
	Display();                                      //!< Конструктор
	void printRandToast();                          //!< Отображает случайный тост на дисплее
	void printInfo( uint16_t volume, uint8_t mode );//!< Отображает информацию на дисплее - (volume - объем рюмки, mode - режим работы)
	void printInfo( uint32_t volume );              //!< Отображает информацию на дисплее - (volume - время работы помпы в сервис режиме)
private:
	Adafruit_SSD1306 * display;                     //!< Указатель на дисплей
};

Display::Display()
{
	display = new Adafruit_SSD1306(128, 32, &Wire);
	display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display->clearDisplay();
	display->display();
	
	Serial.println(F("Display init"));
	
	display->setTextSize(2);
	display->setTextColor(SSD1306_WHITE);
	display->setCursor(0,0);
	display->println(utf8rus("Робот\nРазливайка"));
	display->display();
}

void Display::printRandToast()
{
	display->setTextSize(2);
	display->clearDisplay();
	display->display();
	display->setCursor(0,0);
	display->println(utf8rus(printPGM(random(0, 34))));
	display->display();
}

void Display::printInfo( uint16_t volume, uint8_t mode )
{
	display->setTextSize(4);
	display->clearDisplay();
	display->display();
	display->setCursor(0,0);
	display->println( volume );
	display->setCursor(100,0);
	
	if ( mode == 0 )
		display->println( "M" );
	else if ( mode == 1 )
		display->println( "A" );
	else if ( mode == 2 )
		display->println( "S" );
	
	display->display();
}

void Display::printInfo( uint32_t volume )
{
	display->setTextSize(4);
	display->clearDisplay();
	display->display();
	display->setCursor(0,0);
	display->println( volume );
	display->display();
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

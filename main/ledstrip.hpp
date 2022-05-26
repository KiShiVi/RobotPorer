#ifndef LED_STRIP_H
#define LED_STRIP_H

#include "settings.hpp"
#include <FastLED.h>

/*
*	Класс ленты адресных светодиодов
*
*/


class LedStrip
{
public:
	LedStrip();													//!< Конструктор
	void ledOn( uint8_t pin, uint8_t r, uint8_t g, uint8_t b );	//!< Включить светодиод. pin - позиция светодиода. r/g/b - цвет (0-255)
	void ledOff( uint8_t pin );									//!< Выключить светодиод. pin - позиция светодиода
	
private:
	CRGB leds[LED_COUNT];
};

LedStrip::LedStrip()
{
	FastLED.addLeds <WS2812, LED_PIN, GRB>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness( BRIGHTNESS );
	for( int i = 0 ; i < LED_COUNT; ++i )
		leds[i] = CRGB(0, 0, 0);
	FastLED.show();
	Serial.println(F("LedStrip init"));
}

void LedStrip::ledOn( uint8_t pin, uint8_t r, uint8_t g, uint8_t b )
{
	//Serial.print( "Led ON (pin / R;G;B):	" );
	//Serial.print( pin );
	//Serial.print( " / " );
	//Serial.print( r );
	//Serial.print( ";" );
	//Serial.print( g );
	//Serial.print( ";" );
	//Serial.println( b );
	
	leds[pin] = CRGB(r, g, b);
	FastLED.show();
}

void LedStrip::ledOff( uint8_t pin )
{
	//Serial.print( "Led OFF (pin):	" );
	//Serial.println( pin );
	leds[pin] = CRGB(0, 0, 0);
	FastLED.show();
}

#endif

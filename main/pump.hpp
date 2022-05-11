#ifndef PUMP_H
#define PUMP_H

#include "timer.hpp"

#define DEFAULT_TIMER 2000	//!< Время по умолчанию, которое будет отрабатывать мотор при pumpStart( uint32_t seconds )

/*
*	class Pump - Класс помпы
*/

class Pump
{
public:
    Pump( int pin );					//!< Конструктор. pin - Пин питания на помпу
    void pumpStart();					//!< Включить помпу
    void pumpStart( uint32_t milli );	//!< Включить помпу на milli времени (мс)
    void pumpStop();					//!< Выключить помпу
    uint8_t getState();					//!< Получить состояние помпы (BUSY, READY)
	
	void pumpCheck();					//!< Метод, который следует положить в loop(). Нужен для своевременного отключения по таймеру
    
private:
	Timer * timer;
    int m_pompPin;
    enum{ BUSY, READY } m_state;
};

Pump::Pump( int pin )
{
	timer = new Timer( DEFAULT_TIMER );
    m_state = READY; 
    m_pompPin = pin;
    Serial.println( "Pump init" );
}

void Pump::pumpStart()
{
	if ( m_state == BUSY )
		return;
	timer->start();
	m_state = BUSY;
	digitalWrite( m_pompPin, HIGH );
	Serial.println("Pump started");
}

void Pump::pumpStart( uint32_t milli )
{
	if ( m_state == BUSY )
		return;
	timer->setInterval( milli );
	timer->start();
}

void Pump::pumpStop()
{
	m_state = READY;
	digitalWrite( m_pompPin, LOW );
	Serial.println("Pump stoped");
}

uint8_t Pump::getState()
{
    return m_state;
}

void Pump::pumpCheck()
{
	if ( timer->isReady() && m_state == BUSY )
		pumpStop();
}

#endif

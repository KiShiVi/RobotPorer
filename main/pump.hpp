#ifndef PUMP_H
#define PUMP_H

#include "timer.hpp"

#define DEFAULT_START_TIMER 1000
#define DEFAULT_FINISH_TIMER 2000	//!< Время по умолчанию, которое будет отрабатывать мотор при pumpStart( uint32_t seconds )

/*
*	class Pump - Класс помпы
*/

class Pump
{
public:
    Pump( int pin );					//!< Конструктор. pin - Пин питания на помпу
    void pumpStart( uint32_t milli = DEFAULT_FINISH_TIMER );	//!< Включить помпу на milli времени (мс)
    void pumpStop();					//!< Выключить помпу
    uint8_t getState();					//!< Получить состояние помпы (BUSY, READY)
	bool isWorking();
	
	void pumpCheck();					//!< Метод, который следует положить в loop(). Нужен для своевременного отключения по таймеру
    
private:
	Timer * startTimer;
	Timer * finishTimer;
    int m_pompPin;
    enum{ BUSY = 0, READY = 1 } m_state;
};

Pump::Pump( int pin )
{
	startTimer 	= new Timer( DEFAULT_START_TIMER );
	finishTimer = new Timer( DEFAULT_FINISH_TIMER );
    m_state = READY; 
    m_pompPin = pin;
    Serial.println( "Pump init" );
	
	finishTimer->stop();
	startTimer->stop();
}

void Pump::pumpStart( uint32_t milli )
{
	if ( m_state == BUSY )
	{
		Serial.println( "Pump BUSY" );
		return;
	}
	m_state = BUSY;
	startTimer->start();
	finishTimer->setInterval( milli );
	Serial.println("Pump PRE-START");
}

void Pump::pumpStop()
{
	m_state = READY;
	digitalWrite( m_pompPin, LOW );
	Serial.println("Pump stoped");
	
	finishTimer->stop();
	startTimer->stop();
}

uint8_t Pump::getState()
{
    return m_state;
}

bool Pump::isWorking()
{
	if ( startTimer->getState() == false )
		return true;
	return false;
}

void Pump::pumpCheck()
{
	if ( startTimer->isReady() && m_state == BUSY )
	{
		finishTimer->start();
		digitalWrite( m_pompPin, HIGH );
		Serial.println("Pump started");
		startTimer->stop();
	}
	
	if ( finishTimer->isReady() && m_state == BUSY )
		pumpStop();
}

#endif

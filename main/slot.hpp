#ifndef SLOT_H
#define SLOT_H

#include "timer.hpp"
#include "servocrane.hpp"
#include "pump.hpp"
#include "ledstrip.hpp"

class Slot
{
public:
	Slot( LedStrip * ledStrip, Pump * pump, ServoCrane * servo, uint8_t btnPin, uint8_t slotID, uint8_t slotAngle );
	void slotFirstCheck();
	void slotSecondCheck();
	void slotThirdCheck();
  uint8_t getState();
  
private:
  Timer * btnTimer;
  bool btnState;
	ServoCrane * m_servo;
	Pump * p_pump;
	LedStrip * p_ledStrip;								//!< Указатель на сервис ленты светодиодов
	uint8_t m_btnPin; 									//!< Номер пина концевика
	uint8_t m_slotID; 									//!< ID слота. Должен совпадать с индексом светодиода
	uint8_t m_slotAngle; 								//!< Угол расположения слота (0-180)
	enum{ NO_GLASS, EMPTY, NEXT, PROCESS, READY } m_state;	//!< Статус слота
};

Slot::Slot( LedStrip * ledStrip, Pump * pump, ServoCrane * servo, uint8_t btnPin, uint8_t slotID, uint8_t slotAngle )
{
  btnTimer = new Timer( 100 );
  btnState = false;
	p_ledStrip = ledStrip;
	p_pump = pump;
	m_servo = servo;
	m_btnPin = btnPin;
	m_slotID = slotID;
	m_slotAngle = slotAngle;
	m_state = NO_GLASS;
}

void Slot::slotFirstCheck()
{
	/*
	*	Этап #1. Проверяем нажатие концевика. Включаем красный светодиод если рюмку только
	*	что поставили. Выключаем светодиод, если рюмку убрали. В ручном режиме этот режим нужно включить в loop отдельно, 
	*	чтобы светодиоды закагарились красным до начала разлива
	*
	*/
	// Если концевик НЕ нажат

  if ( btnTimer->isReady() )
    btnState = digitalRead( m_btnPin );
  
	if ( btnState )
	{		
		// У сервопривода будет поле текущего угла. Нужно проверить - если угол серво равен углу слота и статус слота = PROCESS, значит стопаем помпу
		if ( m_servo->getCurrentAngle() == m_slotAngle && ( m_state == PROCESS || m_state == NEXT ) )
		{
			p_pump->pumpStop( false );
		}
			
		if ( m_state != NO_GLASS )
		{
			m_state = NO_GLASS;
			p_ledStrip->ledOff( m_slotID );
		}
	}
	// Если концевик нажат
	else if ( !btnState )
	{
		if ( m_state == NO_GLASS )
		{
			m_state = EMPTY;
			p_ledStrip->ledOn( m_slotID, 255, 0, 0 );
		}
	}
}

void Slot::slotSecondCheck()
{
	/*
	*	Этап #2. После первой проверки проверяем статус. Если рюмка налита красим светодиод в зеленый. 
	*	
	*/

	if ( m_state == PROCESS && p_pump->isFinishedPoured() )
	{
		m_state = READY;
		p_ledStrip->ledOn( m_slotID, 0, 255, 0 );
	}
	
}

void Slot::slotThirdCheck()
{
	/*
	*	Этап #3. После второй проверки проверяем статус. Если рюмка пустует - пытаемся запросить серво и помпу налить в нее. 
	*	
	*/
	if ( m_state == EMPTY && p_pump->getState() != 0 /* m_servo->getState() != BUSY */ )
	{
		m_state = NEXT;
		m_servo->rotate( m_slotAngle );
		p_pump->pumpStart( /* Время заполенния какого-то объема */ );
		p_ledStrip->ledOn( m_slotID, 0, 0, 255 );
	}
	
	if ( m_state == NEXT && p_pump->isPouring() )
	{
		m_state = PROCESS;
		p_ledStrip->ledOn( m_slotID, 255, 255, 0 );
	}
	
}

uint8_t Slot::getState()
{
  return m_state;
}

#endif

/*
*	Примечания: Где-то уровнем выше надо чекать все слоты на статус PROCESS, чтобы в первую очередь проверять именно эту рюмку.
*
*
*
*
*/

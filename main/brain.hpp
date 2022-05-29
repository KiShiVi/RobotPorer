#ifndef BRAIN_H
#define BRAIN_H

/*
*  Основной класс логики программы.
*
*/

#include "timer.hpp"
#include "settings.hpp"
#include <EncButton.h>

#include "slot.hpp"
#include "servocrane.hpp"
#include "pump.hpp"
#include "ledstrip.hpp"
#include "display.hpp"


// Настройка 
const uint8_t BTN_SLOT_PINS[SLOT_COUNT] { A0, A1, A2, A3, 2, 7 };		//!< Пины подключения концевиков и их порядок
const uint8_t SLOT_IDS[SLOT_COUNT]		{ 0, 1, 2, 3, 4, 5 };			//!< Порядковые номера слотов
const uint8_t SLOT_ANGLES[SLOT_COUNT]	{ 175, 143, 109, 71, 35, 5 };	//!< Углы расположения (в градусах) каждого из слота

class Brain
{
  //!< Основной класс логики программы.
public:
	Brain();      //!< Конструктор
	void tick();  //!< Метод, который следует положить в loop(). Постоянно проверяет робота на условия
private:
	void changeAutoManualMode();  //!< Слот, реагирующий на поврот нажатого энкодера
	void changeServiceMode();     //!< Слот, реагирующий на удержание кнопки энкодера
	void incGlassVolume();        //!< Слот, реагирующий на поровот энкодера вправо
	void decGlassVolume();        //!< Слот, реагирующий на поврот энкодера влево
	void mainBtnPressed();        //!< Слот, реагирующий на момент нажатия гланой кнопки
	void mainBtnReleased();       //!< Слот, реагирующий на момент отпускания гланой кнопки
	void mainBtnClick();          //!< Слот, реагирующий на клик гланой кнопки
	void encClicked();            //!< Слот, реагирующий на клик кнопки энкодера

	enum{MANUAL, AUTO, SERVICE} m_mode;             //!< Текущий режим работы робота
	uint16_t 	                m_glassVolume;      //!< Текущий, выставленный пользователем, объем сосуда
	enum{ BUSY, READY }         m_status;           //!< Статус работы робота. Разливает он сейчас что-то или нет
	enum{ STARTED, FINISHED }   m_manualModeFlag;   //!< Стутус для ручного режима работы, чтобы отрабатывать разлив только по нажатию главной кнопки
	bool                        m_toastFlag;        //!< Статус отображения тоста, чтобы отображать только один тост за разлив.

	bool            isStarted;                                        //!< Флаг для задержки работы программы в момент запуска (чтобы успеть отобразить лого)
	Timer       *   p_starterTimer;                                   //!< Таймер задержки работы программы в момент запуска (чтобы успеть отобразить лого)
	uint32_t        p_serviceTime;                                    //!< Время работы помпы в режиме сервиса (после прогона помпы в режиме сервиса пишется время)
	ServoCrane 	*   p_servo;                                          //!< Указатель на объект сервопривода
	Pump 		*   p_pump;                                           //!< Указатель на объект помпы
	LedStrip 	*   p_ledStrip;                                       //!< Указатель на объект светодиодной ленты
	Slot 		**  p_slots;                                          //!< Указатель на указатели объектов слотов
	Display 	*   p_display;                                        //!< Указатель на объект дисплея
	EncButton<EB_TICK, ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN> * p_encoder;//!< Указатель на энкодер (сторонняя библиотека)
	EncButton<EB_TICK, MAIN_BTN_PIN> * p_button;                      //!< Указатель на главную кнопку (сторонняя библиотека)
};

Brain::Brain()
{
	p_starterTimer = new Timer( 3000 );
	isStarted = false;
  
	m_mode = MANUAL;
	m_glassVolume = 20;
	m_toastFlag = false;
	p_servo 	= new ServoCrane( SERVO_PIN );
	p_pump		= new Pump( PUMP_PIN );
	p_ledStrip	= new LedStrip();
	p_slots		= new Slot * [SLOT_COUNT];
	
	for ( int i = 0; i < SLOT_COUNT; ++i )
		p_slots[i] = new Slot( p_ledStrip, p_pump, p_servo, BTN_SLOT_PINS[i], SLOT_IDS[i], SLOT_ANGLES[i], &m_glassVolume );
	
	p_display 	= new Display();
	
	p_encoder 	= new EncButton<EB_TICK, ENC_A_PIN, ENC_B_PIN, ENC_BTN_PIN>;
	p_button 	= new EncButton<EB_TICK, MAIN_BTN_PIN>;

	m_manualModeFlag = FINISHED;
}

void Brain::tick()
{
	if ( !isStarted )
	{
		isStarted = p_starterTimer->isReady();
		return;
	}

	m_status = READY;
	for ( int i = 0; i < SLOT_COUNT; ++i )
	if ( p_slots[i]->getState() == 2 || p_slots[i]->getState() == 3 )
	{
		m_status = BUSY;
		m_manualModeFlag = STARTED;
		if ( !m_toastFlag )
		p_display->printRandToast();
		m_toastFlag = true;
		break;
	}

	if ( m_status == READY && p_servo->getCurrentAngle() != 180 && m_mode != SERVICE && p_pump->getState() != 0 )
		p_servo->rotate( 180 );

	if ( m_status == READY && p_servo->getCurrentAngle() == 180 && m_mode != SERVICE && p_pump->getState() != 0 )
	{
		m_manualModeFlag = FINISHED;
		m_toastFlag = false;
	}

	p_encoder->tick();
	p_button->tick();
	p_pump->pumpCheck();

	if ( m_status == READY )
	{
	if ( p_encoder->rightH() || p_encoder->leftH() )
		changeAutoManualMode();
	else if ( p_encoder->held() )
		changeServiceMode();
	else if ( p_encoder->right() )
		incGlassVolume();
	else if ( p_encoder->left() )
		decGlassVolume();
	else if ( p_encoder->click() )
		encClicked();
	else if ( p_button->press() )
		mainBtnPressed();
	else if ( p_button->release() )
		mainBtnReleased();
	else if ( p_button->click() )
		mainBtnClick();
	}

	if ( m_mode == MANUAL )
	{
		for ( int i = 0; i < SLOT_COUNT; ++i )
		p_slots[i]->slotFirstCheck();
		if ( m_manualModeFlag == STARTED )
		{
			for ( int i = 0; i < SLOT_COUNT; ++i )
				p_slots[i]->slotSecondCheck();
			for ( int i = 0; i < SLOT_COUNT; ++i )
				p_slots[i]->slotThirdCheck();
		}
	}
	else if ( m_mode == AUTO )
	{
		for ( int i = 0; i < SLOT_COUNT; ++i )
			p_slots[i]->slotFirstCheck();
		for ( int i = 0; i < SLOT_COUNT; ++i )
			p_slots[i]->slotSecondCheck();
		for ( int i = 0; i < SLOT_COUNT; ++i )
			p_slots[i]->slotThirdCheck();
	}
	else if ( m_mode == SERVICE )
	{
	for ( int i = 0; i < SLOT_COUNT; ++i )
		p_slots[i]->slotFirstCheck();
	}
}

void Brain::changeAutoManualMode()
{
	Serial.println(F("Mode changed"));
	if ( m_mode != SERVICE )
	{
		if ( m_mode == AUTO )
			m_mode = MANUAL;
		else if ( m_mode == MANUAL )
			m_mode = AUTO;

		p_display->printInfo( m_glassVolume, m_mode );
	}
}

void Brain::changeServiceMode()
{
	Serial.println(F("Mode changed"));
	if ( m_mode == AUTO || m_mode == MANUAL)
	{
		m_mode = SERVICE;
		p_display->printInfo( p_servo->getCurrentAngle(), m_mode );
	}
	else if ( m_mode == SERVICE  && !p_button->hold() )
	{
		m_mode = MANUAL;
		p_display->printInfo( m_glassVolume, m_mode );
	}
}

void Brain::incGlassVolume()
{
	if ( m_mode == AUTO || m_mode == MANUAL )
	{
		m_glassVolume = m_glassVolume >= 250 ? 250 : m_glassVolume + 1;
		p_display->printInfo( m_glassVolume, m_mode );
	}

	else if ( m_mode == SERVICE )
	{
		p_servo->rotate( p_servo->getCurrentAngle() + 1 );
		p_display->printInfo( p_servo->getCurrentAngle(), m_mode );
	}
}

void Brain::decGlassVolume()
{
	if ( m_mode == AUTO || m_mode == MANUAL )
	{
		m_glassVolume = m_glassVolume <= 5 ? 5 : m_glassVolume - 1;
		p_display->printInfo( m_glassVolume, m_mode );
	}

	else if ( m_mode == SERVICE )
	{
		p_servo->rotate( p_servo->getCurrentAngle() - 1 );
		p_display->printInfo( p_servo->getCurrentAngle(), m_mode );
	}
}

void Brain::mainBtnPressed()
{
	Serial.println(F( "MainBTN PRESSED" ) );
	if ( m_mode == AUTO )
		return;
	else if ( m_mode == MANUAL )
		return;
	else if ( m_mode == SERVICE )
	{
		p_serviceTime = millis();
		p_pump->pumpStartWithoutTimer();
	}
}

void Brain::mainBtnReleased()
{
	Serial.println(F("MainBTN RELEASED"));
	if ( m_mode == SERVICE )
	{
		p_display->printInfo( ( millis() - p_serviceTime ) % 100000 );
		p_pump->pumpStop();
	}
}

void Brain::mainBtnClick()
{
	if ( m_mode == MANUAL )
	{
		m_manualModeFlag = STARTED;
	}
}

void Brain::encClicked()
{
	if ( ( m_mode == AUTO || m_mode == MANUAL ) && m_manualModeFlag == FINISHED )
		p_display->printInfo( m_glassVolume, m_mode );

	else if ( m_mode == SERVICE && m_manualModeFlag == FINISHED )
		p_display->printInfo( p_servo->getCurrentAngle(), m_mode );
}

#endif

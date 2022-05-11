#ifndef TIMER_H
#define TIMER_H

/*
*	Класс таймера
* 	Использован улучшенный алгоритм таймера на millis
*	Обеспечивает кратные интервалы и защиту от пропусков и переполнений
*
*/
class Timer
{
public:
	Timer( uint32_t interval );				//!< Конструктор
	void setInterval( uint32_t interval );	//!< Выставляет интервал срабатывания таймера
	boolean isReady();						//!< Возвращает true, когда пришло время
	void reset();							//!< Ручной сброс таймера
	void stop();							//!< Остановка таймера
	void start();							//!< Запуск таймера

private:
	uint32_t m_timer = 0;
	uint32_t m_interval = 0;
	bool m_status = true;
};

Timer::Timer(uint32_t interval) 
{
	m_interval = interval;
	m_timer = millis();
}

void Timer::setInterval(uint32_t interval) 
{
	m_interval = (interval == 0) ? 10 : interval;
}

void Timer::start() 
{
	m_status = true;
	m_timer = millis();
}

void Timer::stop() 
{
	m_status = false;
}

boolean Timer::isReady() 
{
	uint32_t thisMls = millis();
	if (m_status && thisMls - m_timer >= m_interval) 
	{
		do 
		{
			m_timer += m_interval;
			if (m_timer < m_interval) break;
		} while (m_timer < thisMls - m_interval);
		return true;
	} 
	else 
	{
		return false;
	}
}

void Timer::reset() {
	m_timer = millis();
}

#endif

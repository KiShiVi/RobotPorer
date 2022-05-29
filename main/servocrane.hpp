#ifndef SERVO_CRANE_H
#define SERVO_CRANE_H

/*
*  class Pump - Класс для работы с сервоприводом
*  
*/

#include <Servo.h>

class ServoCrane
{
  //!< Класс для работы с сервоприводом
public:
	ServoCrane( uint8_t pin );      //!< Конструктор. pin - Пин управления сервоприводом
	void rotate( uint8_t angle );   //!< Метод поворота сервопривода на угол angle
	uint8_t getCurrentAngle();      //!< Метод, возвращающий текущий угол поврота серво
private:
	Servo * p_servo;                //!< Указатель на серво
	uint8_t m_currentAngle;         //!< Текущий угол поворота серво
};

ServoCrane::ServoCrane( uint8_t pin )
{
	p_servo = new Servo();
	m_currentAngle = 180;
	p_servo->attach( pin );
	p_servo->write( m_currentAngle );
	
	Serial.println(F("ServoCrane init"));
}

void ServoCrane::rotate( uint8_t angle )
{
	if ( angle > 180 || angle < 0 )
		return;
	p_servo->write( angle );
	m_currentAngle = angle;
	Serial.println("ServoCrane rotate to " + angle);
}

uint8_t ServoCrane::getCurrentAngle()
{
	return m_currentAngle;
}



#endif

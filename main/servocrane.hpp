#ifndef SERVO_CRANE_H
#define SERVO_CRANE_H

#include <Servo.h>

class ServoCrane
{
public:
	ServoCrane( uint8_t pin );
	void rotate( uint8_t angle );
	uint8_t getCurrentAngle();
private:
	Servo * p_servo;
    uint8_t m_currentAngle;
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

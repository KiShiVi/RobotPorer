#ifndef SETTINGS_H
#define SETTINGS_H


//Общая настройка
#define SLOT_COUNT 6
#define SERVO_PIN 5
#define PUMP_PIN 6


//Настройка элементов управления
#define MAIN_BTN_PIN 4
#define ENC_BTN_PIN 11
#define ENC_A_PIN 10
#define ENC_B_PIN 8


//Настройка светодиодной ленты
#define BRIGHTNESS 255	//!< Яркость светодиодов
#define LED_PIN 3			//!< Пин подключения светодиодной ленты
#define LED_COUNT 6 	//!< Кол-во светодиодов в ленте


//Настройка помпы
#define DEFAULT_DELAY_TIMER 1500
#define DEFAULT_FINISH_TIMER 2000	//!< Время по умолчанию, которое будет отрабатывать мотор при pumpStart( uint32_t seconds )


#endif

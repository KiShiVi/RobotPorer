#ifndef SETTINGS_H
#define SETTINGS_H

/*
*  Файл настроек робота
*  
*/

//Общая настройка
#define SLOT_COUNT 6        //!< Кол-во слотов
#define SERVO_PIN 5         //!< Пин управления сервоприводом
#define PUMP_PIN 6          //!< Пин питания помпой


//Настройка элементов управления
#define MAIN_BTN_PIN 4      //!< Пин главной кнопки
#define ENC_BTN_PIN 11      //!< Пин кнопки энкодера
#define ENC_A_PIN 10        //!< Пин SW1 энкодера
#define ENC_B_PIN 8         //!< Пин SW2 энкодера


//Настройка светодиодной ленты
#define BRIGHTNESS 255		//!< Яркость светодиодов
#define LED_PIN 3			//!< Пин подключения светодиодной ленты
#define LED_COUNT 6			//!< Кол-во светодиодов в ленте


//Настройка помпы
#define DEFAULT_DELAY_TIMER 1500		//!< Время задержки ДО и ПОСЛЕ разлива
#define DEFAULT_FINISH_TIMER 2000	    //!< Время по умолчанию, которое будет отрабатывать мотор при pumpStart( uint32_t seconds )
#define ONE_HUNDRED_PER_SECOND 12900  	//!< Время, за которое наливается 100мл в мс


#endif

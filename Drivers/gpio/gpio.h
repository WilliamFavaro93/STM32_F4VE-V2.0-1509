/**
  ******************************************************************************
  * @file	myoutputgpio.hpp
  * @author Willam.Favaro
  * @date	20230831
  * @brief	MYGPIO is a struct that refers to a GPIO of the microcontroller.
  *
  ******************************************************************************
  * @note 	The purpose is give a better understanding of the code and
  * 		re-using the same name
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_GPIO_GPIO_H_
#define BSP_GPIO_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <main.h>

/* Defines -------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
	KEY_WAKEUP = 1,
	KEY0,
	KEY1,
	DATA_NCS,
	LED2,
	LED3,
	ESP8266_EN,
} gpio_name_t;

typedef enum
{
	LOW = 0,
	HIGH = 1,
} gpio_pinstate_t;

typedef enum
{
	INPUT = 0,
	OUTPUT,
} gpio_mode_t;

/* Public Functions ----------------------------------------------------------*/
void gpio_set_pinstate(gpio_name_t gpio_name, gpio_pinstate_t pinstate);
gpio_pinstate_t gpio_get_pinstate(gpio_name_t gpio_name);
void gpio_toggle(gpio_name_t gpio_name);

#endif /* BSP_GPIO_GPIO_H_ */

/**
  ******************************************************************************
  * @file	GPIO_4743.h
  * @author Willam.Favaro
  * @date	20240409
  * @brief
  *
  ******************************************************************************
  * @note 	The purpose is give a better understanding of the code and
  * 		re-using the same name
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "main.h"

/* Defines -------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
typedef struct
{
	GPIO_TypeDef* port;
	uint16_t pin;
	gpio_mode_t mode;
} gpio_t;

/* Public Functions ----------------------------------------------------------*/
gpio_t get_gpio(gpio_name_t gpio_name)
{
	gpio_t gpio = {0};

	switch(gpio_name)
	{
	case KEY_WAKEUP:
		gpio.port = GPIOA;
		gpio.pin = GPIO_PIN_0;
		gpio.mode = INPUT;
		break;
	case KEY0:
		gpio.port = GPIOE;
		gpio.pin = GPIO_PIN_4;
		gpio.mode = INPUT;
		break;
	case KEY1:
		gpio.port = GPIOE;
		gpio.pin = GPIO_PIN_3;
		gpio.mode = INPUT;
		break;
	case FLASH_CS:
		gpio.port = GPIOB;
		gpio.pin = GPIO_PIN_0;
		gpio.mode = OUTPUT;
		break;
	case LED2:
		gpio.port = GPIOA;
		gpio.pin = GPIO_PIN_6;
		gpio.mode = OUTPUT;
		break;
	case LED3:
		gpio.port = GPIOA;
		gpio.pin = GPIO_PIN_7;
		gpio.mode = OUTPUT;
		break;
	case ESP8266_EN:
		gpio.port = GPIOB;
		gpio.pin = GPIO_PIN_7;
		gpio.mode = OUTPUT;
	default:
		break;
	}

	return gpio;
}

void gpio_set_pinstate(gpio_name_t gpio_name, gpio_pinstate_t pinstate)
{
	gpio_t gpio = get_gpio(gpio_name);
	HAL_GPIO_WritePin(gpio.port, gpio.pin, pinstate);
}

gpio_pinstate_t gpio_get_pinstate(gpio_name_t gpio_name)
{
	gpio_t gpio = get_gpio(gpio_name);
	return (gpio_pinstate_t)HAL_GPIO_ReadPin(gpio.port, gpio.pin);
}

void gpio_toggle(gpio_name_t gpio_name)
{
	gpio_t gpio = get_gpio(gpio_name);
	gpio_pinstate_t pinstate = gpio_get_pinstate(gpio_name);

	HAL_GPIO_WritePin(gpio.port, gpio.pin, !pinstate);
}

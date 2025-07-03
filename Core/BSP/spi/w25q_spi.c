/**
  ******************************************************************************
  * @file	w25q_spi.c
  * @author Willam.Favaro
  * @date	20240508
  * @brief
  *
  ******************************************************************************
  * @note 	The purpose is give a better understanding of the code and
  * 		re-using the same name
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
/* Includes ------------------------------------------------------------------*/
#include "w25q_spi.h"

/* Defines -------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
const uint32_t Page = 0x100;//porzione piu grande scrivibile
const uint32_t Sector = 0x1000;//porzione piu piccola cancellabile
const uint32_t Block = 0x10000;
const uint32_t Full_memory = 0x800000;//errore se sta per scrivere o leggere in un indirizzo maggiore di questo

const uint32_t MaxFrequency; //104MHz
static const uint32_t Timeout = 1000;

extern SPI_HandleTypeDef hspi1;
static SPI_HandleTypeDef* hspi = &hspi1;

jedec_id_t jedec_id = {0};

uint8_t command = 0;
uint32_t address = 0;
const uint8_t address_size = 3;
const uint8_t status_reg_1_size = 1;

/* Public Functions ----------------------------------------------------------*/
w25q_error_t _abort()
{
	__enable_irq();
	return W25Q_ERROR_COMM_ABORTED;
}

w25q_error_t w25q_spi_read_JEDEC_ID()
{
	command = W25Q_COMMAND_READ_JEDEC_ID;

	//IRQ are disabled to prevent to slow down the message reception
	__disable_irq();
	if(HAL_SPI_Transmit(&hspi1, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Receive(&hspi1, &jedec_id, sizeof(jedec_id), Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_write_enable()
{
	command = W25Q_COMMAND_WRITE_ENABLE;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_read_status_reg_1(uint8_t* status_reg_1)
{
	command = W25Q_COMMAND_READ_STATUS_REGISTER_1;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Receive(hspi, status_reg_1, status_reg_1_size, Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_enable_reset()
{
	command = W25Q_COMMAND_ENABLE_RESET;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_reset_device()
{
	command = W25Q_COMMAND_RESET_DEVICE;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_read_data(uint32_t address_, uint8_t* data, uint32_t data_size)
{
	command = W25Q_COMMAND_READ_DATA;
	address = address_;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Transmit(hspi, &address, address_size, Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Receive(hspi, data, data_size, Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_page_program(uint32_t address_, uint8_t* data, uint32_t data_size)
{
	command = W25Q_COMMAND_PAGE_PROGRAM;
	address = address_;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Transmit(hspi, &address, address_size, Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Transmit(hspi, data, data_size, Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_sector_erase(uint32_t address_)
{
	command = W25Q_COMMAND_SECTOR_ERASE;
	address = address_;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	if(HAL_SPI_Transmit(hspi, &address, address_size, Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

w25q_error_t w25q_spi_chip_erase()
{
	command = W25Q_COMMAND_CHIP_ERASE;

	__disable_irq();
	if(HAL_SPI_Transmit(hspi, &command, sizeof(command), Timeout) != HAL_OK)
		return _abort();
	__enable_irq();

	return W25Q_ERROR_OK;
}

/* Private Functions ---------------------------------------------------------*/
/* EOF -----------------------------------------------------------------------*/

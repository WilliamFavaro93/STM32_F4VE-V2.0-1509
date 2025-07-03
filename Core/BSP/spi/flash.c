/*
 * flash.c
 *
 *  Created on: Mar 27, 2025
 *      Author: William
 */

#include "w25q_spi.h"
#include "flash.h"
#include "main.h"
#include "gpio.h"

#ifdef FLASH_LOG_ENABLED
#define flash_log(...)  printf(...)
#else
#define flash_log(...)  (void)0
#endif

const static gpio_name_t chip_select = FLASH_CS;
static uint8_t status_reg_1 = 0;
static flash_error_t flash_error;

void flash_chip_select()
{
	gpio_set_pinstate(chip_select, GPIO_PIN_RESET);
}

void flash_chip_unselect()
{
	gpio_set_pinstate(chip_select, GPIO_PIN_SET);
}

bool flash_is_ready()
{
	flash_log("%s()", __FUNCTION__);

	flash_chip_select();
	w25q_spi_read_status_reg_1(&status_reg_1);
	flash_chip_unselect();

	return !(status_reg_1 & W25Q_STATUS_REG_1_BUSY);
}

bool flash_is_writeable()
{
	flash_log("%s()", __FUNCTION__);

	flash_chip_select();
	w25q_spi_read_status_reg_1(&status_reg_1);
	flash_chip_unselect();

	return (status_reg_1 & W25Q_STATUS_REG_1_WEL);
}

void flash_soft_reset()
{
	flash_log("%s()", __FUNCTION__);

	flash_chip_select();
	w25q_spi_enable_reset();
	w25q_spi_reset_device();
	flash_chip_unselect();

	HAL_Delay(100);
}

void flash_write_enable()
{
	flash_log("%s()", __FUNCTION__);

	while(!flash_is_ready());

	flash_chip_select();
	w25q_spi_write_enable();
	flash_chip_unselect();
}

flash_error_t flash_read(uint32_t address, uint8_t *data, uint8_t data_size)
{
	flash_log("%s(address = %lu, data_size = %u)", __FUNCTION__, address, data_size);

	while(!flash_is_ready());

	flash_chip_select();
	flash_error = w25q_spi_read_data(address, data, data_size);
	flash_chip_unselect();

	return (flash_error) ? FLASH_ERROR_ABORT : FLASH_ERROR_OK;
}

flash_error_t flash_write(uint32_t address, uint8_t *data, uint8_t data_size)
{
	flash_log("%s(address = %lu, data_size = %u)", __FUNCTION__, address, data_size);

	while(!flash_is_ready());
	flash_write_enable();
	while(!flash_is_writeable());

	flash_chip_select();
	flash_error = w25q_spi_page_program(address, data, data_size);
	flash_chip_unselect();

	return (flash_error) ? FLASH_ERROR_ABORT : FLASH_ERROR_OK;
}

flash_error_t flash_erase(uint32_t sector_index)
{
	flash_log("%s(sector_index = %lu)", __FUNCTION__, sector_index);

	while(!flash_is_ready());
	flash_write_enable();
	while(!flash_is_writeable());

	flash_chip_select();
	flash_error =w25q_spi_sector_erase(sector_index);
	flash_chip_unselect();

	return (flash_error) ? FLASH_ERROR_ABORT : FLASH_ERROR_OK;
}

flash_error_t flash_identify()
{
	flash_log("%s()", __FUNCTION__);

	flash_chip_select();
	flash_error = w25q_spi_read_JEDEC_ID();
	flash_chip_unselect();

	return (flash_error) ? FLASH_ERROR_ABORT : FLASH_ERROR_OK;
}

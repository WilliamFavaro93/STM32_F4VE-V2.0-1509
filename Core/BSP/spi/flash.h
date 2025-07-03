/**
******************************************************************************
  * @file	w25q.h
  * @author Willam.Favaro
  * @date	20240508
  * @brief
  *
  ******************************************************************************
  * @note
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BSP_SPI_FLASH_H_
#define BSP_SPI_FLASH_H_

#include "stdbool.h"

typedef enum
{
	FLASH_ERROR_OK = 0,
	FLASH_ERROR_ABORT = -1,
} flash_error_t;

void flash_init();
void flash_chip_select();
void flash_chip_unselect();
bool flash_is_ready();
bool flash_is_writeable();
void flash_soft_reset();
void flash_write_enable();
flash_error_t flash_read(uint32_t address, uint8_t *data, uint8_t data_size);
flash_error_t flash_write(uint32_t address, uint8_t *data, uint8_t data_size);
flash_error_t flash_erase(uint32_t sector_index);

#endif /* BSP_SPI_FLASH_H_ */

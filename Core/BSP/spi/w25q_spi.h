/**
  ******************************************************************************
  * @file	w25q_spi.h
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
#ifndef W25Q_W25Q_SPI_H_
#define W25Q_W25Q_SPI_H_

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"
#include "stdint.h"
#include "main.h"

/* Defines -------------------------------------------------------------------*/
/* Typedefs ------------------------------------------------------------------*/
typedef enum
{
	W25Q_ERROR_OK = 0,
	W25Q_ERROR_COMM_ABORTED = -1,
} w25q_error_t;

typedef enum
{
	W25Q_COMMAND_READ_STATUS_REGISTER_1 = 0x05,

	W25Q_COMMAND_WRITE_ENABLE = 0x06,
	W25Q_COMMAND_WRITE_DISABLE = 0x04,

	W25Q_COMMAND_READ_DATA = 0x03,
	W25Q_COMMAND_FAST_READ = 0x0B,
	W25Q_COMMAND_PAGE_PROGRAM = 0x02,

	W25Q_COMMAND_FAST_READ_DUAL_OUTPUT = 0x3B,

	W25Q_COMMAND_ERASE_SECURITY_REGISTERS = 0x44,
	W25Q_COMMAND_SECTOR_ERASE = 0x20,

	W25Q_COMMAND_READ_JEDEC_ID = 0x9F,

	W25Q_COMMAND_CHIP_ERASE = 0xC7,

	W25Q_COMMAND_ENABLE_RESET = 0x66,
	W25Q_COMMAND_RESET_DEVICE = 0x99,
} w25q_command_t;

typedef enum
{
	W25Q_STATUS_REG_1_BUSY 	= 0x01,
	W25Q_STATUS_REG_1_WEL 	= 0x02,
} w25q_status_reg_1_t;

typedef enum
{
	W25Q_STATUS_REG_2_QE	= 0x02,
} w25q_status_reg_2_t;
/* Typedefs ------------------------------------------------------------------*/
typedef struct
{
  uint8_t  manufacturer_ID;
  uint8_t  memory_type;
  uint8_t  memory_capacity;
} jedec_id_t;

/* Public Functions ----------------------------------------------------------*/
void w25q_spi_init(SPI_HandleTypeDef* _hspi);
w25q_error_t w25q_spi_read_JEDEC_ID();
w25q_error_t w25q_spi_write_enable();
w25q_error_t w25q_spi_read_status_reg_1(uint8_t* status_reg_1);
w25q_error_t w25q_spi_read_data(uint32_t address, uint8_t* data, uint32_t data_size);
w25q_error_t w25q_spi_page_program(uint32_t address, uint8_t* data, uint32_t data_size);
w25q_error_t w25q_spi_sector_erase(uint32_t address);
w25q_error_t w25q_spi_chip_erase();

#endif /* W25Q_W25Q_SPI_H_ */

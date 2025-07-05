/*
 * w25qxx_littlefs.c
 *
 *  Created on: Mar 24, 2022
 *      Author: lth
 */


#include "littlefs_port.h"
#include "flash.h"
#include "stdint.h"

int littlefs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int littlefs_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int littlefs_erase(const struct lfs_config *c, lfs_block_t block);
int littlefs_sync(const struct lfs_config *c);

__attribute__((section(".ram_d2"), used)) uint8_t lfs_read_buf[LFS_BUFFER_SIZE] = {0};
__attribute__((section(".ram_d2"), used)) uint8_t lfs_prog_buf[LFS_BUFFER_SIZE] = {0};
__attribute__((section(".ram_d2"), used)) uint8_t lfs_file_buf[LFS_BUFFER_SIZE] = {0}; //file buf or cache buf
__attribute__((section(".ram_d2"), used)) uint8_t lfs_lookahead_buf[LFS_BUFFER_SIZE] = {0};	// 128/8=16
__attribute__((section(".ram_d2"), used)) lfs_t lfs = {0};
__attribute__((section(".ram_d2"), used)) lfs_file_t file;

const struct lfs_config lfs_cfg = {
    // block device operations
	.read  = littlefs_read,
	.prog  = littlefs_prog,
	.erase = littlefs_erase,
	.sync  = littlefs_sync,

    // block device configuration
    .read_size = LFS_BUFFER_SIZE,
    .prog_size = LFS_BUFFER_SIZE,
//    .block_size = W25Q_SECTOR,
    .block_size = 0x1000,//non mi lascia inizializzare con un valore costante:extern const uint32_t Sector;
    .block_count = 0x80,
    .cache_size = LFS_BUFFER_SIZE,
    .lookahead_size = LFS_BUFFER_SIZE,
    .block_cycles = 1000,

	.read_buffer = lfs_read_buf,
	.prog_buffer = lfs_prog_buf,
	.lookahead_buffer = lfs_lookahead_buf,
};

int littlefs_port_init()
{
	memset(&lfs, 0, sizeof(lfs));

	memset(&lfs_read_buf, 0, sizeof(lfs_read_buf));
	memset(&lfs_prog_buf, 0, sizeof(lfs_prog_buf));
	memset(&lfs_lookahead_buf, 0, sizeof(lfs_lookahead_buf));

	//monta
	int err = lfs_mount(&lfs, &lfs_cfg);
	LFS_DEBUG("lfs_mount = %i\r\n", err);

	//try another time
	if(err)
	{
		err = lfs_mount(&lfs, &lfs_cfg);
		LFS_DEBUG("lfs_mount = %i\r\n", err);
	}

    if(err)
    {
    	err = lfs_format(&lfs, &lfs_cfg);
    	LFS_DEBUG("lfs_format = %i\r\n", err);

    	err = lfs_mount(&lfs, &lfs_cfg);
    	LFS_DEBUG("lfs_mount = %i\r\n", err);
    }

    return 0;
}

int littlefs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	LFS_DEBUG("LittleFS Read b = 0x%04lx o = 0x%04lx s = 0x%04lx\r", block, off, size);

	if(flash_read(block * c->block_size + off, buffer, size) != FLASH_ERROR_OK)
	{
		LFS_DEBUG("ERROR");
		return -1;
	}

	LFS_DEBUG("OK");
	return 0;
}

int littlefs_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	LFS_DEBUG("LittleFS Prog b = 0x%04lx o = 0x%04lx s = 0x%04lx\r", block, off, size);

	if(flash_write(block * c->block_size + off, buffer, size) != FLASH_ERROR_OK)
	{
		LFS_DEBUG("ERROR");
		return -1;
	}

	LFS_DEBUG("OK");
	return 0;
}

int littlefs_erase(const struct lfs_config *c, lfs_block_t block)
{
	LFS_DEBUG("LittleFS Erase b = 0x%04lx\r", block);

	if(flash_erase(block * c->block_size) != FLASH_ERROR_OK)
	{
		LFS_DEBUG("ERROR");
		return -1;
	}

	LFS_DEBUG("OK");

	return 0;
}

int littlefs_sync(const struct lfs_config *c)
{
	LFS_DEBUG("LittleFS Sync\r");

	return 0;
}

int filesystem_recovery(const char * filename, void * buffer, int32_t buffer_size)
{
	LFS_DEBUG("app_recovery\r\n");
	memset(&file, 0, sizeof(file));
	memset(buffer, 0, buffer_size);

	 struct lfs_info info;

	 if(lfs_stat(&lfs, filename, &info) == LFS_ERR_OK)
	 {
		 LFS_DEBUG("file exists\r");
	 }
	 else
	 {
		 LFS_DEBUG("file doesnt exists\r");
		 return -1;
	 }

	int err = lfs_file_open(&lfs, &file, filename, LFS_O_RDWR | LFS_O_CREAT);
	if(err == LFS_ERR_OK)
	{
		LFS_DEBUG("lfs_file_opencfg = %i\r\n", err);

		err = lfs_file_read(&lfs, &file, buffer, buffer_size);
		LFS_DEBUG("lfs_file_read = %i\r\n", err);

		err = lfs_file_close(&lfs, &file);
		LFS_DEBUG("lfs_file_close = %i\r\n", err);

		return 0;
	}

	return -1;
}

int filesystem_backup(const char * filename, void * buffer, int32_t buffer_size)
{
	memset(&file, 0, sizeof(file));

	int err = lfs_file_open(&lfs, &file, filename, LFS_O_RDWR | LFS_O_CREAT);
	if(err == LFS_ERR_OK)
	{
		LFS_DEBUG("lfs_file_opencfg = %i\r\n", err);

		err = lfs_file_write(&lfs, &file, buffer, buffer_size);
		LFS_DEBUG("lfs_file_write = %i\r\n", err);

		err = lfs_file_close(&lfs, &file);
		LFS_DEBUG("lfs_file_close = %i\r\n", err);

		return 0;
	}

	return -1;
}

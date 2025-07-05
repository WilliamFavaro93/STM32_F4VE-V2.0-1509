/*
 * w25qxx_littlefs.h
 *
 *  Created on: Mar 24, 2022
 *      Author: lth
 */

#ifndef W25QXX_LITTLEFS_H_
#define W25QXX_LITTLEFS_H_

#include "lfs.h"
//#include "BSP\bsp_conf.h"

#define 	LFS_BUFFER_SIZE		0x100

int littlefs_port_init();
int filesystem_recovery(const char * filename, void * buffer, int32_t buffer_size);
int filesystem_backup(const char * filename, void * buffer, int32_t buffer_size);

#endif /* W25QXX_LITTLEFS_H_ */

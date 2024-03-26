#ifndef _FLASH_DISKIO_H
#define _FLASH_DISKIO_H

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

DSTATUS FLASH_disk_status();
DSTATUS FLASH_disk_initialize();
DSTATUS FLASH_disk_read(BYTE *buff, LBA_t sector, UINT count);
DSTATUS FLASH_disk_write(const BYTE *buff, LBA_t sector, UINT count);
// DSTATUS FLASH_disk_ioctl();

#endif /* _FLASH_DISKIO_H */
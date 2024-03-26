#include "sdram_diskio.h"

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "sdram.h"

DSTATUS FLASH_disk_status()
{
    return FR_OK;
}

DSTATUS FLASH_disk_initialize()
{
    return FR_OK;
}

DSTATUS FLASH_disk_read(BYTE *buff, LBA_t sector, UINT count)
{
    (void)sector;
    
    flash_read(0x00100000ULL, buff, count);

    return FR_OK;
}

DSTATUS FLASH_disk_write(const BYTE *buff, LBA_t sector, UINT count)
{
    (void)sector;

    flash_write(0x00100000ULL, buff, count);
    return FR_OK;
}
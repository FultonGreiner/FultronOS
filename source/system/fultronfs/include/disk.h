#ifndef _DISK_H
#define _DISK_H

#include <stdbool.h>
#include <string.h>

#include "super_block.h"

typedef void   (*disk_open_t)    (char *, size_t);
typedef size_t (*disk_size_t)    (void);
typedef bool   (*disk_mounted_t) (void);
typedef void   (*disk_mount_t)   (void);
typedef void   (*disk_read_t)    (int, char *);
typedef void   (*disk_write_t)   (int, char *);
typedef void   (*disk_erase_t)   (int, char *);

typedef struct _Disk {
    size_t         block_size;
    disk_open_t    open;
    disk_size_t    size;
    disk_mounted_t mounted;
    disk_mount_t   mount;
    disk_read_t    read;
    disk_write_t   write;
    disk_erase_t   erase;

    block_t        block;
} Disk;

Disk *get_sdram_disk(void);

#endif /* _DISK_H */
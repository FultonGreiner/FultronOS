#ifndef _FULTRON_FS_H
#define _FULTRON_FS_H

#include <stdbool.h>
#include <string.h>

#include "disk.h"

typedef void   (*fs_debug)  (Disk *disk);
typedef void   (*fs_format) (Disk *disk);
typedef bool   (*fs_mount)  (Disk *disk);
typedef size_t (*fs_create) (void);
typedef bool   (*fs_remove) (size_t inumber);
typedef size_t (*fs_stat)   (size_t inumber);
typedef size_t (*fs_read)   (size_t inumber, char *data, size_t length, size_t offset);
typedef size_t (*fs_write)  (size_t inumber, char *data, size_t length, size_t offset);

typedef struct _FileSystem {
    fs_debug  debug;
    fs_format format;
    fs_mount  mount;
    fs_create create;
    fs_remove remove;
    fs_stat   stat;
    fs_read   read;
    fs_write  write;
} FileSystem;

FileSystem *get_sdram_fs(void);

#endif /* _FULTRON_FS_H */
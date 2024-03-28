#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "disk.h"
#include "printf.h"
#include "fultronfs.h"
#include "super_block.h"

void   fultronfs_debug   (Disk *disk);
void   fultronfs_format  (Disk *disk);
bool   fultronfs_mount   (Disk *disk);
size_t fultronfs_create  (void);
bool   fultronfs_remove  (size_t inumber);
size_t fultronfs_stat    (size_t inumber);
size_t fultronfs_read    (size_t inumber, char *data, size_t length, size_t offset);
size_t fultronfs_write   (size_t inumber, char *data, size_t length, size_t offset);

static FileSystem file_system =
{
    .debug  = &fultronfs_debug,
    .format = &fultronfs_format,
    .mount  = &fultronfs_mount,
    // .create = &fultronfs_create,
    // .remove = &fultronfs_remove,
    // .stat   = &fultronfs_stat,
    // .read   = &fultronfs_read,
    // .write  = &fultronfs_write,
};

FileSystem *get_sdram_fs(void)
{
    return &file_system;
}

#define FULTRONFS_SUPERBLOCK_DEBUG_FMT  ( \
                                            "SuperBlock:\r\n" \
                                            "\t%lu blocks:\r\n" \
                                            "\t%lu inode blocks:\r\n" \
                                            "\t%lu inodes:\r\n" \
                                        )

void fultronfs_debug(Disk *disk)
{
    printf(FULTRONFS_SUPERBLOCK_DEBUG_FMT,
            disk->block.super.blocks,
            disk->block.super.inode_blocks,
            disk->block.super.inodes
        );

    for (uint32_t i = 1; i < disk->block.super.inode_blocks; i++)
    {
        printf("\ni: %lu\r\n", i);
        printf("inode_blocks: %lu\r\n", disk->block.super.inode_blocks);
        printf("comp: %lu\r\n\n", i < disk->block.super.inode_blocks);

        printf("Inode %ld:\r\n", i);
        printf("\tsize: %d bytes\r\n", disk->block.inodes[i].size);

        size_t direct_blocks;
        for (size_t j = 0; j < FULTRONFS_DIRECT_BLOCK_COUNT; j++)
        {
            if (disk->block.inodes[i].direct[j] != 0)
            {
                direct_blocks++;
            }
        }

        printf("\tdirect blocks: %ld\r\n", direct_blocks);

        // return;
    }
}

/**
* @brief Creates a new filesystem on the disk, destroying any data already
*        present. Sets aside ten percent of the blocks for inodes, clears the 
*        inode table, and writes the superblock. Returns true on success, false 
*        otherwise.
* 
* @param disk The disk to format.
*/
void fultronfs_format(Disk *disk)
{
    disk->erase(0, disk->size());
    printf("fultronfs_format()\r\n");
}

bool fultronfs_mount(Disk *disk)
{
    printf("fultronfs_mount()\r\n");
    return true;
}
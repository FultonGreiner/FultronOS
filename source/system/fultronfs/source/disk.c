#include <stdbool.h>
#include <string.h>

#include "disk.h"
// #include "fultronfs_config.h"
#include "printf.h"
#include "sdram.h"
#include "super_block.h"

#define TEST_BASE (0x00100000ULL)

void   disk_open    (const char *path, size_t nblocks);
size_t disk_size    (void);
bool   disk_mounted (void);
void   disk_mount   (void);
void   disk_read    (int blocknum, char *rx_buffer);
void   disk_write   (int blocknum, char *tx_buffer);

static size_t Blocks = 0;
static size_t Mounts = 0;

static Disk sdram_disk =
{
    .block_size = 512,
    .open = &disk_open,
    .size = &disk_size,
    .mounted = &disk_mounted,
    .mount = &disk_mount,
    .read = &disk_read,
    .write = &disk_write,

    .block = 
    {
        .super =
        {
            .blocks = 0,
            .inode_blocks = 0,
            .inodes = 0,
            .magic_number = FULTRONFS_MAGIC_NUMBER,
        },
    },
};

Disk *get_sdram_disk(void)
{
    return &sdram_disk;
}

void disk_open(const char *path, size_t nblocks)
{
    Blocks = nblocks;
    printf("disk_open()\r\n");
}

size_t disk_size(void)
{
    printf("disk_size(): 0x%x blocks.\r\n", Blocks);
    return Blocks;
}

bool disk_mounted(void)
{
    printf("disk_mounted()\r\n");
    return Mounts > 0;
}

void disk_mount(void)
{
    printf("disk_mount()\r\n");
    Mounts++;
}

void disk_read(int blocknum, char *rx_buffer)
{
    sdram_read(TEST_BASE, rx_buffer, sizeof(rx_buffer));
    printf("disk_read(): reading '%s' from block number %d.\r\n", rx_buffer, blocknum);
}

void disk_write(int blocknum, char *tx_buffer)
{
    sdram_write(TEST_BASE, tx_buffer, sizeof(tx_buffer));
    printf("disk_write(): writing '%s' to block number %d.\r\n", tx_buffer, blocknum);
}

void disk_erase(int blocknum, uint32_t size)
{
    sdram_erase(TEST_BASE, size);
    printf("disk_erase(): erasing %u bytes from block number %d.\r\n", size, blocknum);
}
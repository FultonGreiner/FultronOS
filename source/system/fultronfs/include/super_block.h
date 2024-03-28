#ifndef _SUPER_BLOCK_H
#define _SUPER_BLOCK_H

#include <stdint.h>
#include <string.h>

#include "fultronfs_config.h"

#define FULTRONFS_MAGIC_NUMBER     (0xF0F03410ULL)

typedef struct super_block
{
    uint32_t magic_number; /* used to verify if the disk is mounted */
    uint32_t blocks;       /* total number of blocks */
    uint32_t inode_blocks; /* number of blocks reserved for inodes, selected by format() */
    uint32_t inodes;       /* total number of inodes in the inode blocks */
} super_block_t;

typedef struct indirect_block
{
    uint32_t *data_blocks[FULTRONFS_DATA_BLOCK_COUNT];
} indirect_block_t;

typedef struct inode
{
    uint32_t         valid;             /* 1 if the inode has been created */
    uint32_t         size;              /* size of the inode in bytes */
    uint32_t         direct[FULTRONFS_DIRECT_BLOCK_COUNT]; /* pointers to data blocks */
    indirect_block_t indirect;  /* pointer to indirect block */
} inode_t;

typedef struct data_block
{
    char data[FULTRONFS_BLOCK_SIZE_BYTES];
} data_block_t;

typedef union block {
    super_block_t super;                              /* super block */
    inode_t       inodes[FULTRONFS_INODES_PER_BLOCK]; /* inode block */
    // uint32_t      pointers[FULTRONFS_POINTERS_PER_BLOCK];   // Pointer block
    // char        Data[Disk::BLOCK_SIZE];         // Data block
} block_t;

#endif /* _SUPER_BLOCK_H */
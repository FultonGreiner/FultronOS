#include <stdint.h>
#include <string.h>

#include "device.h"

size_t device_write(fd_t fd, char *tx_buffer, size_t length)
{
    return 0;
}

fd_t device_open(chardev_t *chardev)
{
    return FD_0;
}

chardev_t *get_device(device_id_t device_id)
{
    chardev_t *device = NULL;
    return device;
}
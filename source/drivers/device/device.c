#include "device.h"

static fd_t fd_count = FD_0;

fd_t device_open(device_id_t device_id)
{
    fd_t fd = FD_INVALID;

    fd = fd_count++;

    return fd;
}
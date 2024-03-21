#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>
#include <string.h>

typedef enum fd
{
    FD_0 = 0, /* TODO: add more fds */
    FD_NUM,
    FD_INVALID = -1,
} fd_t;

typedef enum device_id
{
    DEVICE_ID_UART1 = 0,
    DEVICE_ID_UART2,
    DEVICE_ID_NUM,
} device_id_t;

typedef fd_t    (*device_read_t)     (device_id_t device_id, char *rx_buffer, size_t length);
typedef fd_t    (*device_write_t)    (device_id_t device_id, char *tx_buffer, size_t length);
typedef int32_t (*device_ioctl_t)    (device_id_t device_id, uint32_t cmd, uint32_t params);
typedef int32_t (*device_open_t)     (device_id_t device_id);
typedef int32_t (*device_release_t)  (device_id_t device_id);

typedef struct device_driver
{
    device_read_t     read;       /* A non-negative return value represents the number of bytes successfully read. */
    device_write_t    write;      /* The return value, if non-negative, represents the number of bytes successfully written. */
    device_ioctl_t    ioctl;      /* If the device method returns a non-negative value, the same value is passed back to the calling program to indicate successful completion. */
    device_open_t     open;       /* If this entry is NULL, opening the device always succeeds, but your driver isn’t notified. */
    device_release_t  release;    /* This operation is invoked when the file structure is being released. Like open, release can be missing. */
} device_driver_t;

typedef enum device_type
{
    DEVICE_TYPE_UART = 0,
    DEVICE_TYPE_NUM,
} device_type_t;

typedef struct device
{
    device_driver_t *driver;
    device_id_t id;
    device_type_t type;
} device_t;

// device_ioctl_t   driver_ioctl;
// device_open_t    driver_init;
// device_read_t    driver_read;
// device_release_t driver_release;
// device_write_t   driver_write;

fd_t device_open(device_id_t device_id);

#endif /* _DEVICE_H */
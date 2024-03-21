#ifndef _DEVICE_H
#define _DEVICE_H

#include <stdint.h>
#include <string.h>

typedef struct device_driver
{
    size_t (*read)(void);       /* A non-negative return value represents the number of bytes successfully read. */
    size_t (*write)(uint8_t);   /* The return value, if non-negative, represents the number of bytes successfully written. */
    int (*ioctl)(void);         /* If the device method returns a non-negative value, the same value is passed back to the calling program to indicate successful completion. */
    int (*open)(void);          /* If this entry is NULL, opening the device always succeeds, but your driver isn’t notified. */
    int (*release)(char *);     /* This operation is invoked when the file structure is being released. Like open, release can be missing. */
} device_driver_t;

typedef enum device_id
{
    DEVICE_ID_UART1 = 0,
    DEVICE_ID_NUM,
} device_id_t;

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

#endif /* _DEVICE_H */
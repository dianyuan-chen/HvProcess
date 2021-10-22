#ifndef SPI_BUS_H__
#define SPI_BUS_H__

#include "Std_Types.h"
#include "Dio.h"

struct spi_bus_gpio_cs {
    uint8 flags;
    Dio_ChannelType ioChannel;
};

typedef Std_ReturnType (*spi_init_func)(void *private_data, uint8 flags);
typedef void (*spi_deinit_func)(void *private_data);
typedef Std_ReturnType (*spi_select_func)(void *private_data, uint8 which, uint8 is_select);
typedef Std_ReturnType (*spi_transmit_byte_func)(void *private_data, uint8 *b);
typedef uint16 (*spi_transfer_func)(void *private_data, uint8 *r, const uint8 *w, uint16 len);


struct spi_operations {
    spi_init_func init;
    spi_deinit_func deinit;
    spi_select_func select;
    spi_transmit_byte_func transmit_byte;
    spi_transfer_func transfer;
};

struct spi_bus {
    void *private_data;
    const struct spi_operations *ops;
};

uint16 spi_transfer_use_transmit_onebyte(void *private_data, const struct spi_operations *ops, uint8 *r, const uint8 *w, uint16 len);


typedef const struct spi_bus *spi_bus_t;

#define SPI_FLAG_CLK_IDLE_HIGH     0x01U
#define SPI_FLAG_CLK_IDLE_LOW      0x00U
#define SPI_FLAG_CLK_FIRST_EDGE    0x02U
#define SPI_FLAG_CLK_SECOND_EDGE   0x00U
#define SPI_FLAG_LSB_FIRST         0x04U
#define SPI_FLAG_MSB_FIRST         0x00U
#define SPI_FLAG_HARDWARE_SS       0x08U
#define SPI_FLAG_INVERT_CS         0x10U
#define SPI_FLAG_RECFG             0x20U

#define spi_init(bus, flags) (bus)->ops->init((bus)->private_data, flags)
#define spi_deinit(bus) (bus)->ops->deinit((bus)->private_data)
#define spi_select(bus, which, is_select) (bus)->ops->select((bus)->private_data, which, is_select)
#define spi_transmit_byte(bus, b) (bus)->ops->transmit_byte((bus)->private_data, b)
#define spi_transfer(bus, r, w, len)  (bus)->ops->transfer((bus)->private_data, r, w, len)

#endif

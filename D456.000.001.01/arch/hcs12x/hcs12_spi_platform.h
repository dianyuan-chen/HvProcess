#ifndef __HCS12_SPI_PRIVATE_H__
#define __HCS12_SPI_PRIVATE_H__

#include "hcs12_spi.h"
#include "derivative.h"
#include "Dio.h"

struct hcs12_spi_regs {
    volatile SPI0CR1STR cr1;
    volatile SPI0CR2STR cr2;
    volatile SPI0BRSTR br;
    volatile SPI0SRSTR sr;
    volatile SPI0DRSTR dr;
};

struct hcs12_spi_platform {
    struct hcs12_spi_regs *near regs;
    uint8 baud_reg_value;
    uint8 cs_num;
    const struct spi_bus_gpio_cs *cs_pins;
};

extern const struct spi_operations hcs12_spi_ops;



#endif

#ifndef __HCS12_SPI_H__
#define __HCS12_SPI_H__

#include "spi_bus.h"

typedef const struct hcs12_spi_platform *hcs12_spi_t;

Std_ReturnType hcs12_spi_init(hcs12_spi_t spi, uint8 flags);
Std_ReturnType hcs12_spi_transmit_byte(hcs12_spi_t spi, uint8 *dat);
uint16 hcs12_spi_transfer(hcs12_spi_t spi, uint8 *r, const uint8 *w, uint16 len);
Std_ReturnType hcs12_spi_select(const struct hcs12_spi_platform *platform, uint8 which, uint8 is_select);
void hcs12_spi_deinit(const struct hcs12_spi_platform *platform);

#endif

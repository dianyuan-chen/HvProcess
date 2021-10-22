#ifndef LOCKABLE_SPI_H
#define LOCKABLE_SPI_H

#include "spi_bus.h"

typedef struct {
    uint8 prio;
    uint8 inited;
    struct spi_bus bus;
} LockableSpi_Type;

extern const struct spi_operations LockableSpi_Ops;

Std_ReturnType LockableSpi_Init(LockableSpi_Type *spi, uint8 flags);
Std_ReturnType LockableSpi_TransmitByte(const LockableSpi_Type *spi, uint8 *dat);
uint16 LockableSpi_Transfer(const LockableSpi_Type *spi, uint8 *r, const uint8 *w, uint16 len);
Std_ReturnType LockableSpi_Select(LockableSpi_Type *spi, uint8 which, uint8 is_select);
void LockableSpi_Deinit(LockableSpi_Type *spi);

#endif

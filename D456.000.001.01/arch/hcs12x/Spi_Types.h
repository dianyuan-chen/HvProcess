#ifndef SPI_TYPES_H
#define SPI_TYPES_H

#include "Dio.h"

typedef uint8    Spi_ChannelType ;
typedef uint8    Spi_JobType;
typedef uint8    Spi_SequenceType;
typedef uint16   Spi_NumberOfDataType;
typedef uint8    Spi_DataType;
typedef uint8    Spi_HWUnitType;
typedef uint8    Spi_ExternalDeviceTypeType;

#define SPI_CH_NOT_VALID    (0xff)
#define SPI_JOB_NOT_VALID   (0xff)
#define SPI_SEQ_NOT_VALID   (0xff)

typedef struct {
    vuint8 xx;

} Spi_HwRegisterType;

typedef struct Spi_HwConfig {
    uint8 Activated;
    Spi_HwRegisterType *__near HwReg;
} Spi_HwConfigType;

#endif
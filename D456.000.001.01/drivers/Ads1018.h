#ifndef ADS1018_H
#define ADS1018_H

#include "Std_Types.h"
#include "spi_bus.h"
#include "Dio.h"
#include "Ads1018_Cfg.h"

typedef void (*Ads1018_NewSampleValue)(sint16 value);

typedef uint8 Ads1018_IndexType;

typedef struct {
    uint8 cfgh;
    uint8 cfgl;
    Ads1018_NewSampleValue cbk;
} Ads1018_SequenceConfigType;

typedef struct {
    Ads1018_IndexType startIndex;
    Ads1018_IndexType endIndex;
    Dio_ChannelType rdy;
    struct spi_bus bus;
} Ads1018_BusConfigType;

void Ads1018_Init(void);
void Ads1018_Start(Ads1018_IndexType index, const Ads1018_SequenceConfigType *sequence);
void Ads1018_Stop(Ads1018_IndexType index);
void Ads1018_TryReadBus(uint8 busIndex);

extern const Ads1018_BusConfigType Ads1018BusConfigData[ADS1018_BUS_NUM];

#endif

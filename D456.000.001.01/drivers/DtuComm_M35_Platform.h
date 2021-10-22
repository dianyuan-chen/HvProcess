#ifndef DTUCOMM_M35_PLATFORM_H__
#define DTUCOMM_M35_PLATFORM_H__

#include "DtuComm_M35.h"
#include "Dio.h"
#include "Uart.h"
#include "atcmd_Abstract.h"

typedef struct {
    Uart_ChannelType uart;
    Dio_ChannelType keyDo;
    boolean isKeyHighAssert;
    Dio_ChannelType pwrDo;
    boolean isPwrHighEnable;
    Dio_ChannelType statusDi;
    Dio_PortLevelType ioLevelWhenPowerOn;
    ATCmd_DataType atcmdPrivate;
    uint8 currentUsedModule;
} DtuCommM35_ConfigType;

#endif
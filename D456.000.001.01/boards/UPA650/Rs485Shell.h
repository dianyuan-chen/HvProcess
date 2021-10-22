#ifndef RS485SHELL_H__
#define RS485SHELL_H__

#include "Platform_Types.h"
#include "Std_Types.h"
#include "Uart.h"
#define UARTSHELL_NUM 1U

#define UARTSHELL_CHANNEL_RS485 0

typedef struct {
    const uint8 channl;
    const uint32 baud;
    Uart_RxIndication prxindication;
} UartShell_ConfigType;

extern const UartShell_ConfigType UartShellConfigType[UARTSHELL_NUM + 1U];

extern Std_ReturnType UartShell_Init(const UartShell_ConfigType *UartShellConfigType, uint8 index);

extern void idleShell_rx(void *UserData, uint8 dat);

extern void rs485Shell_rx(void *UserData, uint8 dat);

#endif



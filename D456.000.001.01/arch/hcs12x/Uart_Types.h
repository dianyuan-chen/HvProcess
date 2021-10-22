#ifndef UART_TYPES_H
#define UART_TYPES_H

#include "RingBuffer.h"

typedef struct {
    uint8 BDH_ASR1;
    uint8 BDL_ACR1;
    uint8 CR1_ACR2;
    uint8 CR2;
    uint8 SR1;
    uint8 SR2;
    uint8 DRH;
    uint8 DRL;
} Uart_HwRegType;

typedef struct {
    Uart_HwRegType *near Register;
    RingBuffer_Type *syncTxBuffer;
} Uart_ConfigTypes;

#endif
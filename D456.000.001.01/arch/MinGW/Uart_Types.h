#ifndef UART_TYPES_H
#define UART_TYPES_H

typedef struct {
    const char *portname;
    RingBuffer_Type *syncTxBuffer;
} Uart_ConfigTypes;

#endif
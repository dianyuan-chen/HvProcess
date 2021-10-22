#ifndef __ATCMD_MC20_H__
#define __ATCMD_MC20_H__

#include "atcmd_Abstract.h"
#include "ucos_ii.h"
#include "Uart.h"
#include "ComStack_Types.h"

typedef struct ATCMDMC20_IPDataConfig {
    BufReq_ReturnType (*StartOfReception)(PduLengthType length);
    BufReq_ReturnType (*CopyRxData)(const uint8 *dat, PduLengthType length);
    void (*RxIndication)(NotifResultType Result);
} ATCMDMC20_IPDataConfigType;


typedef struct ATCMDMC20_PrivateData {
    const ATCMDMC20_IPDataConfigType *IPDataConfig;
    RingBuffer_Type *mATReplyBuffer;
    Uart_ChannelType uart;
    OS_EVENT *mEvent;
    uint32 time_serial_recv_default;
    uint16 ipd_recv_index;
    uint16 ipd_length;
    uint8 expect_length;
    uint8 rxbuf_index1;
    uint8 rxbuf_index2;
    uint8 rxbuf_filled;
    uint8 rxbuf1[50];
    uint8 rxbuf2[50];
    uint8 rxbuf_which;
    uint8 auto_reply_index;
    uint8 auto_reply_buffer[50];
    uint8 mIPDDataBuffer[50];
    uint8 mIPDataRxIndex;
    uint8 *head_recv_buf;
    void (*serial_recv_func)(struct ATCMDMC20_PrivateData *data, uint8 b);
} ATCMDMC20_PrivateDataType;


extern const ATCmd_OperationsType ATCmd_Operations_MC20;

#endif
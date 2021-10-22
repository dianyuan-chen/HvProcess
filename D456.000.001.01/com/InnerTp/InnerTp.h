#ifndef INNERTP_H
#define INNERTP_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Async_Event.h"
#include "PduR.h"

Std_ReturnType InnerTp_Transmit(PduIdType SduId, const PduInfoType *InfoPtr);

typedef struct InnerTp_RequestHandler {
    PduIdType cmdPduId;
    PduIdType replyPduId;
    void (*handle)(const struct InnerTp_RequestHandler* requestHandler, const PduInfoType *InfoPtr);
} InnerTp_RequestHandlerType;


typedef struct {
    uint8 requestHandlerNumber;
    const InnerTp_RequestHandlerType *requestHandlers;
    RingBuffer_Type *requestRingBuffer;
    uint8 requestDataBufferLength;
    uint8 *requestDataBuffer;
} InnerTp_ConfigDataType;


Std_ReturnType InnerTp_Init(Async_LooperType *looper, const InnerTp_ConfigDataType *configDataPtr);

#define InnerTp_StartOfReception   PduR_InnerTpStartOfReception
#define InnerTp_CopyRxData          PduR_InnerTpCopyRxData
#define InnerTp_RxIndication   PduR_InnerTpRxIndication

#endif

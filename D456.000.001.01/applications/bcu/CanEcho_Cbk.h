#ifndef ECHO_H__
#define ECHO_H__

#include "ComStack_Types.h"

#define CANECHO_SDUID_RX_1 0
#define CANECHO_SDUID_RX_2 1
#define CANECHO_SDUID_RX_3 2
#define CANECHO_SDUID_TX_1 0
#define CANECHO_SDUID_TX_2 1
#define CANECHO_SDUID_TX_3 2

void CanEcho_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void CanEcho_TxConfirmation(PduIdType RxPduId);

#endif

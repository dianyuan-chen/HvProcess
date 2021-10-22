#ifndef _CANTP_CBK_H_
#define _CANTP_CBK_H_

#include "CanTp_Cfg.h"
#include "ComStack_Types.h"

extern void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
extern void CanTp_TxConfirmation(PduIdType CanTpTxPduId);

#endif


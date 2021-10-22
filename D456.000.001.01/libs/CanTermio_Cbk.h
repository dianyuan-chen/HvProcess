#ifndef CANTERMIO_CBK_H__
#define CANTERMIO_CBK_H__

#include "Std_Types.h"
#include "ComStack_Types.h"

#include "Termio_Cfg.h"

void CanTermio_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void CanTermio_TxConfirmation(PduIdType TxPduId);

#endif

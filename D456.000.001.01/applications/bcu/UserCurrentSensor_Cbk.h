#ifndef USERCURRENTSENSOR_Cbk_H__
#define USERCURRENTSENSOR_Cbk_H__

#include "ComStack_Types.h"


void UserCurrentSensor_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void UserCurrentSensor_TxConfirmation(PduIdType RxPduId);

#endif
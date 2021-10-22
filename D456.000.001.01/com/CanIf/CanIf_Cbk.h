#ifndef _CANIF_CBK_H_
#define _CANIF_CBK_H_

#include "CanIf_Cfg.h"
#include "CanIf_Types.h"

extern void CanIf_TxConfirmation(PduIdType CanTxPduId);
extern void CanIf_RxIndication(Can_HwHandleType Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);
#if(CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON) 
extern void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr);
#endif

extern void CanIf_ControllerBusOff(uint8 Controller);
extern void CanIf_ControllerWakeUp(uint8 Controller); 
extern void CanIf_ControllerModeIndication(uint8 Controller, CanIf_ControllerModeType ControllerMode);

#endif


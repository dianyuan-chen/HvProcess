#ifndef _DCM_CBK_H_
#define _DCM_CBK_H_

#include "ComStack_Types.h"

extern BufReq_ReturnType Dcm_StartOfReception(const PduIdType DcmRxPduId, const PduLengthType TpSduLength, PduLengthType *const Length);
extern BufReq_ReturnType Dcm_CopyRxData(const PduIdType DcmRxPduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
extern void Dcm_RxIndication(const PduIdType DcmRxPduId, const NotifResultType Result);
extern BufReq_ReturnType Dcm_CopyTxData(const PduIdType DcmTxPduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);
extern void Dcm_TxConfirmation(const PduIdType DcmTxPduId, const NotifResultType Result);

#endif

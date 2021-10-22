#ifndef DTU_TP_H
#define DTU_TP_H

#include "Std_Types.h"
#include "ComStack_Types.h"

#define DTUTP_PDUID_UDS_PHYICAL 0

Std_ReturnType DtuTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType *TpTxInfoPtr);

#endif

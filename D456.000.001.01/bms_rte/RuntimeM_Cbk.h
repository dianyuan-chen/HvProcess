#ifndef RUNTIMEM_CBK_H_
#define RUNTIMEM_CBK_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

void RuntimeM_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
#define RuntimeM_TxConfirmation NULL

#endif

/**
 * \}
 */

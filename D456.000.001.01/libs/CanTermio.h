#ifndef CAN_TERMIO_H__
#define CAN_TERMIO_H__

#include "ComStack_Types.h"

typedef struct {
    uint8 endOfLine;
    uint8 firstByteOfStdinFrame;
} CanTermio_ConfigType;

extern const PduIdType PduId_CANIF_TX_CANTERMIO;
extern const PduIdType PduId_CANIF_RX_CANTERMIO;
extern const CanTermio_ConfigType CanTermioConfigData;

#endif

#ifndef _CANIF_TYPE_H_
#define _CANIF_TYPE_H_

typedef enum {
    CANIF_CS_UNINIT = 0,
    CANIF_CS_SLEEP = 1,
    CANIF_CS_STARTED = 2,
    CANIF_CS_STOPPED = 3
} CanIf_ControllerModeType;


typedef enum {
    CANIF_SET_OFFLINE           = 0,
    CANIF_SET_ONLINE            = 1,
    CANIF_SET_RX_OFFLINE        = 2,
    CANIF_SET_RX_ONLINE         = 3,
    CANIF_SET_TX_OFFLINE        = 4,
    CANIF_SET_TX_OFFLINE_ACTIVE = 5,
    CANIF_SET_TX_ONLINE         = 6
} CanIf_PduSetModeType;

typedef enum {
    CANIF_GET_OFFLINE                  = 0,
    CANIF_GET_OFFLINE_ACTIVE           = 4,
    CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE = 5,
    CANIF_GET_ONLINE                   = 7,
    CANIF_GET_RX_ONLINE                = 1,
    CANIF_GET_TX_ONLINE                = 6
} CanIf_PduGetModeType;

typedef enum {
    CANIF_NO_NOTIFICATION    = 0,
    CANIF_TX_RX_NOTIFICATION = 1
} CanIf_NotifStatusType ;

#endif

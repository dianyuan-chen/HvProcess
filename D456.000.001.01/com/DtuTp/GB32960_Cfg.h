#ifndef GB32960_CFG_H
#define GB32960_CFG_H

#include "DtuComm_M35.h"
#include "RuntimeM.h"

void GBRtMsg_Start(void);
void GBRtMsg_Cancel(void);

#define GB32960_DCM_TX_PDUID           0U
#define GB32960_DCM_RX_PDUID           0U
#define GB32960_NOTIFY_OTA_REQUEST     RuntimeM_RequestOta
#define GB32960_NOTIFY_DISCONNECTED    GBRtMsg_Cancel
#define GB32960_NOTIFY_CONNECTED       GBRtMsg_Start
#define GB32960_GET_CCID               DtuM35_GetCCID
#define GB32960_TCP_CONNECT            DtuM35_TcpConnect
#define GB32960_TCP_TRANSMIT           DtuM35_TcpTransmit
#define GB32960_TCP_DISCONNECT         DtuM35_TcpDisconnect

#endif

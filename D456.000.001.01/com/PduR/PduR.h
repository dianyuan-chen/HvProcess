/**
 * \file PduR.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 通信路由头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161215 |
 */

#ifndef PDUR_H_
#define PDUR_H_

#include "ComStack_Types.h"

#define PDUR_NONE 0xFFU
#define NONE_PDUID_0 0x00U

/**
 * \brief CAN通信PduId路由配置类型定义
 */
typedef struct{
    uint8 Module; /**< 模块类型 */
    PduIdType PduId; /**< PduId */
} PduR_PduIdConfigType;

/**
 * \brief Tp通信路由上下文类型定义
 */
typedef struct{
    // Upper layer
    const PduR_PduIdConfigType *DcmPduIdConfig;
    const PduR_PduIdConfigType *ChargerCommPduIdConfig;
    const PduR_PduIdConfigType *InternalCommPduIdConfig;
    const PduR_PduIdConfigType *VcuCommPduIdConfig;
    const PduR_PduIdConfigType *ExternCanCommPduIdConfig;

    // Tp layer
    const PduR_PduIdConfigType *CanTpTxPduIdConfig;
    const PduR_PduIdConfigType *CanTpRxPduIdConfig;
    const PduR_PduIdConfigType *DtuTpTxPduIdConfig;
    const PduR_PduIdConfigType *DtuTpRxPduIdConfig;
    const PduR_PduIdConfigType *J1939TpTxPduIdConfig;
    const PduR_PduIdConfigType *J1939TpRxPduIdConfig;
    const PduR_PduIdConfigType *InnerTpTxPduIdConfig;
    const PduR_PduIdConfigType *InnerTpRxPduIdConfig;
}PduR_ConfigType;

/**
 * \brief PduR通信路由配置参数
 */
extern const PduR_ConfigType PduR_ConfigInfo;
extern const PduR_ConfigType *PduR_Config;

/**
 * \brief PduR通信路由初始化函数
 *
 * \param ConfigInfoPtr 通信路由配置参数
 */
void PduR_Init(const PduR_ConfigType *ConfigInfoPtr);

// PduR ChargeComm
Std_ReturnType PduR_ChargerCommTransmit(PduIdType PduId, const PduInfoType* PduInfoPtr);

// PduR Dcm
Std_ReturnType PduR_DcmTransmit(PduIdType PduId, const PduInfoType* PduInfoPtr);

// PduR VcuComm
Std_ReturnType PduR_VcuCommTransmit(PduIdType PduId, const PduInfoType* PduInfoPtr);

// PduR InternalComm
Std_ReturnType PduR_InternalCommTransmit(PduIdType PduId, const PduInfoType* PduInfoPtr);

// PduR ExternCanComm
Std_ReturnType PduR_ExternCanCommTransmit(PduIdType PduId, const PduInfoType* PduInfoPtr);


// PduR DtuTp
void PduR_DtuTpRxIndication(const PduIdType PduId, const NotifResultType Result);
void PduR_DtuTpTxConfirmation(PduIdType PduId, const NotifResultType Result);
BufReq_ReturnType PduR_DtuTpStartOfReception(const PduIdType PduId, const PduLengthType SduLength, PduLengthType *const BufferSizePtr);
BufReq_ReturnType PduR_DtuTpCopyRxData(const PduIdType PduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
BufReq_ReturnType PduR_DtuTpCopyTxData(const PduIdType PduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);

// PduR CanTp
void PduR_CanTpRxIndication(const PduIdType PduId, const NotifResultType Result);
void PduR_CanTpTxConfirmation(PduIdType PduId, const NotifResultType Result);
BufReq_ReturnType PduR_CanTpStartOfReception(const PduIdType PduId, const PduLengthType SduLength, PduLengthType *const BufferSizePtr);
BufReq_ReturnType PduR_CanTpCopyRxData(const PduIdType PduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
BufReq_ReturnType PduR_CanTpCopyTxData(const PduIdType PduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);

// PduR J1939Tp
void PduR_J1939TpRxIndication(const PduIdType PduId, const NotifResultType Result);
void PduR_J1939TpTxConfirmation(PduIdType PduId, const NotifResultType Result);
BufReq_ReturnType PduR_J1939TpStartOfReception(const PduIdType PduId, const PduLengthType SduLength, PduLengthType *const BufferSizePtr);
BufReq_ReturnType PduR_J1939TpCopyRxData(const PduIdType PduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
BufReq_ReturnType PduR_J1939TpCopyTxData(const PduIdType PduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);

// PduR LtcTp
void PduR_LtcTpRxIndication(const PduIdType PduId, const NotifResultType Result);
void PduR_LtcTpTxConfirmation(PduIdType PduId, const NotifResultType Result);
BufReq_ReturnType PduR_LtcTpStartOfReception(const PduIdType PduId, const PduLengthType SduLength, PduLengthType *const BufferSizePtr);
BufReq_ReturnType PduR_LtcTpCopyRxData(const PduIdType PduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
BufReq_ReturnType PduR_LtcTpCopyTxData(const PduIdType PduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);

// PduR InnerTp
void PduR_InnerTpRxIndication(const PduIdType PduId, const NotifResultType Result);
void PduR_InnerTpTxConfirmation(PduIdType PduId, const NotifResultType Result);
BufReq_ReturnType PduR_InnerTpStartOfReception(const PduIdType PduId, const PduLengthType SduLength, PduLengthType *const BufferSizePtr);
BufReq_ReturnType PduR_InnerTpCopyRxData(const PduIdType PduId, const PduInfoType *const PduInfoPointer, PduLengthType *const RxBufferSizePtr);
BufReq_ReturnType PduR_InnerTpCopyTxData(const PduIdType PduId, const PduInfoType *const PduInfoPtr, const RetryInfoType *const RetryInfoPtr, PduLengthType *const TxDataCntPtr);


#endif

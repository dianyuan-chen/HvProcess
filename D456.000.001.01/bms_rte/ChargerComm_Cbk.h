/**
 * \file ChargerComm_Cbk.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电机通信回调函数头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup ChargerComm 充电机通信
 * \{
 */


#ifndef CHARGERCOMM_CBK_H_
#define CHARGERCOMM_CBK_H_

#include "ComStack_Types.h"
#include "Async_Event.h"

/**
 * \brief 数据帧发送间隔
 */
#define CHARGERCOMM_IPDU_SEND_INTERNAL          1U
#define CHARGERCOMM_IPDU_RETRY_SEND_INTERNAL    5U
#define CHARGERCOMM_DIRECT_IPDU_CONFIRM_TIMEOUT 1000U
#define CHARGERCOMM_CMDT_IPDU_CONFIRM_TIMEOUT   1500U

/**
 * \brief 无数据发送的空闲正时时间
 */
#define CHARGERCOMM_SEND_STATE_IDLE_TIMEOUT     2000U

/**
 * \brief 新消息接收回调函数
 * \note 接收到新消息，以PduId确认消息类型，通过PduInfoPtr获取消息数据
 *
 * \param PduId 消息对应的PduId
 * \param PduInfoPtr 消息数据缓存及长度信息
 */
void ChargerComm_ReceiveMessageNewIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);


/**
 * \brief 充电机通信发送确认函数
 *
 * \param TxPduId 发送PduId
 * \param Result 发送结果
 */
void ChargerComm_TxConfirmation(
    const PduIdType       TxPduId,
    const NotifResultType Result
);

/**
 * \brief 充电机通信接收到消息回调函数
 *
 * \param sduIndex 接收到的消息的PduId
 * \param Result 接收到消息的状态
 */
void ChargerComm_RxIndication(
    PduIdType sduIndex,
    NotifResultType Result
);

/**
 * \brief 充电机通信启动接收回调函数
 * \details 启动接收时通过此回调函数获取数据的接收资源
 *
 * \param sduIndex 启动接收消息的PduId
 * \param TpSduLength 接收消息的长度
 * \param Length 上层可提供的消息的最大缓存
 * \return E_OK:缓存获取成功 E_NOT_OK:缓存获取失败
 */
BufReq_ReturnType ChargerComm_StartOfReception(
    PduIdType       sduIndex,
    PduLengthType   TpSduLength,
    PduLengthType   *Length
);


/**
 * \brief 充电机通信拷贝接收到的数据函数
 * \details 根据接收到的PduId拷贝接收到的数据
 *
 * \param RxPduId 待接收数据的PduId
 * \param PduInfoPointer 接收的数据
 * \param RxBufferSizePtr 上层可提供的剩余接收缓存大小
 *
 * \return 缓存大小请求结果
 */
BufReq_ReturnType ChargerComm_CopyRxData(
    const PduIdType     RxPduId,
    const PduInfoType   *const PduInfoPointer,
    PduLengthType       *const RxBufferSizePtr
);

/**
 * \brief 充电机通信拷贝待发送的数据函数
 * \details 根据发送PduId拷贝待发送的数据
 *
 * \param CanTxPduId 待发送数据的PduId
 * \param PduInfoPtr 待发送的数据信息
 * \param RetryInfoPtr 保留未使用
 * \param TxDataCntPtr 调用此函数后剩余待发送数据大小
 *
 * \return 缓存大小请求结果
 */
BufReq_ReturnType ChargerComm_CopyTxData(
    const PduIdType     CanTxPduId,
    const PduInfoType   *const PduInfoPtr,
    const RetryInfoType *const RetryInfoPtr,
    PduLengthType       *const TxDataCntPtr
);

/**
 * \brief 充电机通信发送Cmdt事件回调函数
 * \details 充电机通信延时发送事件，主要用于保证帧发送间隔
 *
 * \param event 事件类型
 * \param trigger 事件触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType ChargerComm_SendCmdtAsyncEventCbk(Async_EventType *event, uint8 trigger);

/**
 * \brief 充电机通信发送Direct事件回调函数
 * \details 充电机通信延时发送事件，主要用于保证帧发送间隔
 *
 * \param event 事件类型
 * \param trigger 事件触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType ChargerComm_SendDirectAsyncEventCbk(Async_EventType *event, uint8 trigger);

/**
 * \brief 接收超时异步事件
 * \details 用于接收超时计时及超时事件处理
 *
 * \param event 异步事件
 * \param trigger 触发类型
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType ChargerComm_RecAsyncEventCbk(const Async_EventType *event, uint8 trigger);


#endif


/**
 * \}
 */
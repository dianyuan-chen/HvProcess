/**
 * \addtogroup InternalComm 内网通信
 * \{
 */

#ifndef INTERNALCOMM_CBK_H_
#define INTERNALCOMM_CBK_H_

#include "InternalComm.h"
#include "Async_Event.h"

/**
 * \brief 内网通信从机DID定义
 */
#define INTERNALCOMM_SLAVE_CELL_VOLTAGE_DID             0x480U
#define INTERNALCOMM_SLAVE_CELL_TEMPERATURE_DID         0x484U
#define INTERNALCOMM_SLAVE_CELL_BALANCE_BYTE_DID        0x488U
#define INTERNALCOMM_SLAVE_TEMPERATURE_TYPE_DID         0x48BU
#define INTERNALCOMM_SLAVE_TEMPERATURE_TYPE_CFG_DID     0x48CU
#define INTERNALCOMM_SLAVE_CELL_BALANCE_BITMAP_DID      0x48DU
#define INTERNALCOMM_SLAVE_CELL_HSS_STATUS_DID          0x900U
#define INTERNALCOMM_SLAVE_CELL_HSS_VOLTAGE_DID         0x901U
#define INTERNALCOMM_SLAVE_CELL_HSS_CURRENT_DID         0x902U
#define INTERNALCOMM_SLAVE_CELL_DIGITAL_INPUT_DID       0xF10U
#define INTERNALCOMM_SLAVE_CELL_ANALOG_INPUT_DID        0xF30U
#define INTERNALCOMM_SLAVE_BOARD_VOLTAGE_DID            0x1600U
#define INTERNALCOMM_SLAVE_BOARD_TEMPERATURE_DID        0x1620U
#define INTERNALCOMM_FW_VERSION_DID                     0xA50CU
#define INTERNALCOMM_HW_ID_DID                          0xA50DU


typedef enum{
  INTERNALCOMM_SCHEDULE_ITEM_0x480 = 0,
  INTERNALCOMM_SCHEDULE_ITEM_0x484 = 1,
  INTERNALCOMM_SCHEDULE_ITEM_0x488 = 2,
  INTERNALCOMM_SCHEDULE_ITEM_0x900 = 3,
  INTERNALCOMM_SCHEDULE_ITEM_0x901 = 4,
  INTERNALCOMM_SCHEDULE_ITEM_0x902 = 5,
  INTERNALCOMM_SCHEDULE_ITEM_0xF10 = 6,
  INTERNALCOMM_SCHEDULE_ITEM_0xF30 = 7,
  INTERNALCOMM_SCHEDULE_ITEM_0x1600 = 8,
  INTERNALCOMM_SCHEDULE_ITEM_0x1620 = 9,
  INTERNALCOMM_SCHEDULE_ITEM_0xA50C = 10,
  INTERNALCOMM_SCHEDULE_ITEM_0xA50D = 11,
  INTERNALCOMM_SCHEDULE_ITEM_0x48B = 12,
  INTERNALCOMM_SCHEDULE_ITEM_0x48C = 13,
  INTERNALCOMM_SCHEDULE_ITEM_0x48D = 14,
  INTERNALCOMM_SCHEDULE_ITEM_MAX = 15,
  INTERNALCOMM_SCHEDULE_ITEM_INVALID = 0xFF
}InternalComm_ScheduleItemIndexType;

/**
 * \brief 内网通信发送确认函数
 *
 * \param TxPduId 发送PduId
 * \param Result 发送结果
 */
void InternalComm_TxConfirmation(
    const PduIdType       TxPduId,
    const NotifResultType Result
);

/**
 * \brief 内网通信接收到消息回调函数
 *
 * \param sduIndex 接收到的消息的PduId
 * \param Result 接收到消息的状态
 */
void InternalComm_RxIndication(
       PduIdType sduIndex,
       NotifResultType Result);

/**
 * \brief 内网通信启动接收回调函数
 * \details 启动接收时通过此回调函数获取数据的接收资源
 *
 * \param sduIndex 启动接收消息的PduId
 * \param TpSduLength 接收消息的长度
 * \param Length 上层可提供的消息的最大缓存
 * \return E_OK:缓存获取成功 E_NOT_OK:缓存获取失败
 */
BufReq_ReturnType InternalComm_StartOfReception(
       PduIdType       sduIndex,
       PduLengthType   TpSduLength,
       PduLengthType   *Length);

/**
 * \brief 内网通信拷贝接收到的数据函数
 * \details 根据接收到的PduId拷贝接收到的数据
 *
 * \param RxPduId 待接收数据的PduId
 * \param PduInfoPointer 接收的数据
 * \param RxBufferSizePtr 上层可提供的剩余接收缓存大小
 *
 * \return 缓存大小请求结果
 */
BufReq_ReturnType InternalComm_CopyRxData(
       const PduIdType     RxPduId,
       const PduInfoType   *const PduInfoPointer,
       PduLengthType       *const RxBufferSizePtr);

/**
 * \brief 内网通信拷贝待发送的数据函数
 * \details 根据发送PduId拷贝待发送的数据
 *
 * \param CanTxPduId 待发送数据的PduId
 * \param PduInfoPtr 待发送的数据信息
 * \param RetryInfoPtr 保留未使用
 * \param TxDataCntPtr 调用此函数后剩余待发送数据大小
 *
 * \return 缓存大小请求结果
 */
BufReq_ReturnType InternalComm_CopyTxData(
       const PduIdType     CanTxPduId,
       const PduInfoType   *const PduInfoPtr,
       const RetryInfoType *const RetryInfoPtr,
       PduLengthType       *const TxDataCntPtr);


/**
 * \brief 内网通信接收事件回调函数
 * \details 增加重试计数，如果计数超时设定值，则置位全局通信异常标志并重新启动下一个从机的请求；
 *
 * \param event 事件类型
 * \param trigger 事件触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType InternalComm_ReceiveAsyncEventCbk(InternalComm_AsyncEventType *event, uint8 trigger);

/**
 * \brief 内网通信发送事件回调函数
 * \details 复位发送状态，重启从机DID请求
 *
 * \param event 事件类型
 * \param trigger 事件触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType InternalComm_SendAsyncEventCbk(InternalComm_AsyncEventType *event, uint8 trigger);

/**
 * \brief 内网通信启动发送事件回调函数
 * \details 复位发送状态，重启从机DID请求
 *
 * \param event 事件类型
 * \param trigger 事件触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType InternalComm_StartReceptionAsyncEventCbk(InternalComm_AsyncEventType *event, uint8 trigger);

/**
 * \brief 获取请求DID通信的数据
 * \details 向DataBufferPtr中写入需要请求的DID的请求数据
 *
 * \param SlaveNum 从机号
 * \param Did 待请求DID
 * \param Length 缓存大小,返回写入的长度
 */
void InternalComm_GetRequireDidData(
  App_SlaveIdType SlaveNum,
  InternalComm_DidTypes Did,
  InternalComm_MsgType DataBufferPtr,
  InternalComm_MsgLenType *Length);

/**
 * \brief SID处理派发函数
 * \details 根据当前接收数据的SID信息，将不同SID数据交由不同的SID处理函数处理
 *
 * \param Context 请求通道上下文
 */
Std_ReturnType InternalComm_ReceiveSidDispatch(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 获取从机温感类型配置数据回调函数
 * \details 通过从机号及DID将配置从机温感类型的数据组包到DataBufferPtr中，并将组包的长度通过Length返回
 *
 * \param SlaveNum 从机号
 * \param Did 控制DID
 * \param DataBufferPtr 组包数据存放缓存
 * \param Length 返回实际组包长度
 */
void InternalComm_GetTemperatureTypeSendData_Cbk(App_SlaveIdType SlaveId, InternalComm_DidTypes Did, InternalComm_MsgType DataBufferPtr, InternalComm_MsgLenType *Length);

/**
 * \brief 内网通信DID异步超时回调函数
 * \details 此函数会将DID写入各发送通道的发送缓存中，当前发送接收通道不空闲，则置为Pending状态，否则直接触发请求报文发送
 *
 * \param Event 异步事件类型
 * \param byWhat 触发原因
 *
 * \return 请参考\link Async_EvnetCbkReturnType \endlink
 */
Async_EvnetCbkReturnType InternalComm_RequestDID0x480_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x484_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x488_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x900_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x901_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x902_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0xF10_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0xF30_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x1600_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x1620_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0xA50C_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0xA50D_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x48B_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x48C_Cbk(Async_EventType *Event, uint8 byWhat);
Async_EvnetCbkReturnType InternalComm_RequestDID0x48D_Cbk(Async_EventType *Event, uint8 byWhat);



#endif

/** \} */
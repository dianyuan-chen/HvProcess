/**
 * \addtogroup InternalComm 内网通信
 * \{
 */

#ifndef INTERNALCOMM_H
#define INTERNALCOMM_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "CanTp.h"
#include "InternalComm_Cfg.h"
#include "App_Types.h"
#include "SystemConnection.h"
#include "Dcm_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

/**
 * \brief DID参数值定义
 */
#define INTERNALCOMM_INVALID_DID_VALUE                  (0xFFFFU)
#define INTERNAMCOMM_SLAVE_FIRST_DID_VALUE              INTERNALCOMM_SLAVE_TEMPERATURE_TYPE_DID

/**
 * \brief 缓存大小定义
 */
#define INTERNALCOMM_TX_LOOPER_CMD_BUFF_SIZE            (100U)

#define INTERNALCOMM_PENDING_DID_BUFF_SIZE              (100U)

/**
 * \brief 从机温感表配置失败重试次数
 */
#define INTERNALCOMM_TEMP_TYPE_CFG_RETRY_NUM            (5U)

/**
 * \brief 发送会话状态
 */
#define INTERNALCOMM_DIAG_IDLE                          (0x00U)
#define INTERNALCOMM_DIAG_TX                            (0x01U)
#define INTERNALCOMM_DIAG_TX_CONFIRM                    (0x02U)
/**
 * \brief 接收会话状态
 */
#define INTERNALCOMM_DIAG_RX_REC_WAITING                (0x01U)
#define INTERNALCOMM_DIAG_RX_RECEIVING                  (0x02U)
#define INTERNALCOMM_DIAG_RX_INDICATION                 (0x03U)
#define INTERNALCOMM_DIAG_RX_PROCESSING                 (0x04U)


/**
 * \brief 内网通信接收超时发送重试参数
 */
#define INTERNALCOMM_SEND_RETRY_NUM                     (0x02U)
#define INTERNALCOMM_RECEIVE_ERROR_NUM                  (0x02U)

/**
 * \brief 内网通信SID定义
 */
#define INTERNALCOMM_REQUIRE_DID_SID                    (0x22U)
#define INTERNALCOMM_WIRTE_DID_SID                      (0x2EU)
#define INTERNALCOMM_INPUT_OUTPUT_SID                   (0x2FU)
#define INTERNALCOMM_NEGATIVE_RESPONSE_SID              (0x7FU)

/**
 * \brief 内网通信否定应答码定义
 */
#define INTERNALCOMM_NRC_POSITIVERESPONSE                               (0x00U)
#define INTERNALCOMM_NRC_GENERALREJECT                                  (0x10U)
#define INTERNALCOMM_NRC_SERVICENOTSUPPORTED                            (0x11U)
#define INTERNALCOMM_NRC_SUBFUNCTIONNOTSUPPORTED                        (0x12U)
#define INTERNALCOMM_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT          (0x13U)
#define INTERNALCOMM_NRC_BUSYREPEATREQUEST                              (0x21U)
#define INTERNALCOMM_NRC_CONDITIONSNOTCORRECT                           (0x22U)
#define INTERNALCOMM_NRC_REQUESTSEQUENCEERROR                           (0x24U)
#define INTERNALCOMM_NRC_REQUESTOUTOFRANGE                              (0x31U)
#define INTERNALCOMM_NRC_SECURITYACCESSDENIED                           (0x33U)
#define INTERNALCOMM_NRC_INVALIDKEY                                     (0x35U)
#define INTERNALCOMM_NRC_EXCEEDNUMBEROFATTEMPTS                         (0x36U)

/**
 * \brief 通道请求上下文操作宏
 */
#define InternalComm_Get_ReqChannelCxtPtr(index)        (&InternalComm_ReqChannelCxt[index])
#define InternalComm_SlaveNumIsValid(slave)             ((slave) < SystemConnection_ConfigInfo.SlaveNum)

#define InternalComm_SetBit(value, bit)                 ((value) |= (uint16)((uint16)1U << (bit)))
#define InternalComm_ClrBit(value, bit)                 ((value) &= (uint16)(((uint16)1U << (bit)) ^ 0xFFFFU))
#define InternalComm_BitTest(value, bit)                ((value) & (uint16)((uint16)1U << (bit)))

#define InternalComm_SetLBit(value, bit)                ((value) |= ((1UL) << (bit)))
#define InternalComm_ClrLBit(value, bit)                ((value) &= (((1UL) << (bit)) ^ 0xFFFFUL))
#define InternalComm_LBitTest(value, bit)               ((value) & (1UL << (bit)))

#define InternalComm_Get_PendingDidRbPtr()              (&(Context->PendingDidRb))
#define InternalComm_Get_ChannelNum()                   (Context->ChannelNum)
#define InternalComm_Get_CurrendDid()                   (Context->CurrentDid)
#define InternalComm_Get_CurrentSlave()                 (Context->CurrentSlave)
#define InternalComm_Get_SlaveMaskBit()                 (Context->SlaveMaskBit)
#define InternalComm_Get_ChlSlaveMask()                 (Context->ChlSlaveMask)
#define InternalComm_Get_SendDiagState()                (Context->SendDiagState)
#define InternalComm_Get_SendRetryCnt()                 (Context->SendRetryCnt)
#define InternalComm_Get_SendDataPtr(x)                 (&Context->SendDataPtr[x])
#define InternalComm_Get_SendDataLen()                  (Context->SendDataLen)
#define InternalComm_Get_AvailableSendDataLen()         (Context->AvailableSendDataLen)
#define InternalComm_Get_GetSendDataFunc()              (Context->GetSendDataFunc)
#define InternalComm_Get_XgateFlag()                    (Context->XgateFlag)
#define InternalComm_Get_ReceiveErrorCnt()              (Context->ReceiveErrorCnt)
#define InternalComm_Get_ReceiveDiagState()             (Context->ReceiveDiagState)
#define InternalComm_Get_ReceiveSlave()                 (Context->ReceiveSlave)
#define InternalComm_Get_ReceiveDataPtr(x)              (&Context->ReceiveDataPtr[x])
#define InternalComm_Get_ReceiveData(x)                 (Context->ReceiveDataPtr[x])
#define InternalComm_Get_ReceiveDataLen()               (Context->ReceiveDataLen)
#define InternalComm_Get_AvailableRecBufferSize()       (Context->AvailableRecBufferSize)
#define InternalComm_Get_StartSlave()                   (InternalComm_ReqChlSlaveRangeCfg[Context->ChannelNum].StartSlave)
#define InternalComm_Get_StopSlave()                    (InternalComm_ReqChlSlaveRangeCfg[Context->ChannelNum].StopSlave)

#define InternalComm_Set_ChannelNum(x)                  (Context->ChannelNum = (x))
#define InternalComm_Set_CurrentDid(x)                  (Context->CurrentDid = (x))
#define InternalComm_Reset_CurrentDid()                 (Context->CurrentDid = INTERNALCOMM_INVALID_DID_VALUE)
#define InternalComm_Set_CurrentSlave(x)                (Context->CurrentSlave = (x))
#define InternalComm_Reset_CurrentSlave()               (Context->CurrentSlave = 0xFFU)
#define InternalComm_Set_SlaveMaskBit(x)                (Context->SlaveMaskBit = (x))
#define InternalComm_Clr_SlaveMaskBit()                 (Context->SlaveMaskBit = 0U)
#define InternalComm_Reset_SlaveMaskBit()               (Context->SlaveMaskBit = 0U)
#define InternalComm_Set_ChlSlaveMask(x)                (Context->ChlSlaveMask = (x))
#define InternalComm_Reset_ChlSlaveMask()               (Context->ChlSlaveMask = 0U)
#define InternalComm_Set_SendDiagState(x)               (Context->SendDiagState = (x))
#define InternalComm_Reset_SendDiagState()              (Context->SendDiagState = INTERNALCOMM_DIAG_IDLE)
#define InternalComm_Increase_SendRetryCnt()            (Context->SendRetryCnt++)
#define InternalComm_Reset_SendRetryCnt()               (Context->SendRetryCnt = 0U)
#define InternalComm_Set_SendDataPtr(x)                 (Context->SendDataPtr = (x))
#define InternalComm_Reset_SendDataPtr()                (Context->SendDataPtr = InternalComm_TxMsgBuffer[Context->ChannelNum])
#define InternalComm_Set_SendDataLen(x)                 (Context->SendDataLen = (x))
#define InternalComm_Clr_SendDataLen()                  (Context->SendDataLen = 0U)
#define InternalComm_Reset_AvailableSendDataLen()       (Context->AvailableSendDataLen = InternalComm_Get_SendDataLen())
#define InternalComm_Set_AvailableSendDataLen(x)        (Context->AvailableSendDataLen = (x))
#define InternalComm_Clr_AvailableSendDataLen()         (Context->AvailableSendDataLen = 0U)
#define InternalComm_Set_GetSendDataFunc(x)             (Context->GetSendDataFunc = (x))
#define InternalComm_Clr_GetSendDataFunc()              (Context->GetSendDataFunc = NULL)
#define InternalComm_Set_XgateFlag()                    (Context->XgateFlag = TRUE)
#define InternalComm_Clr_XgateFlag()                    (Context->XgateFlag = FALSE)
#define InternalComm_Increase_ReceiveErrorCnt()         (Context->ReceiveErrorCnt++)
#define InternalComm_Reset_ReceiveErrorCnt()            (Context->ReceiveErrorCnt = 0U)
#define InternalComm_Set_ReceiveErrorCnt(x)             (Context->ReceiveErrorCnt = (x))
#define InternalComm_Set_ReceiveDiagState(x)            (Context->ReceiveDiagState = (x))
#define InternalComm_Reset_ReceiveDiagState()           (Context->ReceiveDiagState = INTERNALCOMM_DIAG_IDLE)
#define InternalComm_Set_ReceiveSlave(x)                (Context->ReceiveSlave = (x))
#define InternalComm_Reset_ReceiveSlave()               (Context->ReceiveSlave = 0xFFU)
#define InternalComm_Set_ReceiveDataPtr(x)              (Context->ReceiveDataPtr = (x))
#define InternalComm_Reset_ReceiveDataPtr()             (Context->ReceiveDataPtr = InternalComm_RxMsgBuffer[Context->ChannelNum])
#define InternalComm_Set_ReceiveDataLen(x)              (Context->ReceiveDataLen = (x))
#define InternalComm_Clr_ReceiveDataLen()               (Context->ReceiveDataLen = 0U)
#define InternalComm_Set_AvailableRecBufferSize(x)      (Context->AvailableRecBufferSize = (x))
#define InternalComm_Reset_AvailableRecBufferSize()     (Context->AvailableRecBufferSize = INTERNALCOMM_RX_BUFF_SIZE)

/**
 * \brief 获取从机对应的发送通道
 */
#define INTERNALCOMM_SLAVE_TO_CHANNEL(SLAVE)            ((SLAVE) % INTERNALCOMM_REQUIRE_CHANNEL_NUM)


struct InternalComm_DIDReadScheduleItem;

/**
 * \brief DID类型定义
 */
typedef uint16 InternalComm_DidTypes;

/**
 * \brief 内网通信否定应答码类型定义
 */
typedef uint8 InternalComm_NegativeResponseCode;

/**
 * \brief 内网通信消息类型定义
 */
typedef uint8 InternalComm_MsgItemType;

typedef InternalComm_MsgItemType *InternalComm_MsgType;

/**
 * \brief 内网通信消息长度类型定义
 */
typedef uint16 InternalComm_MsgLenType;

/**
 * \brief 内网通信从机位掩码类型定义
 */
typedef uint16 InternalComm_SlaveBitMaskType;

typedef struct _InternalComm_ReqChannelCxtType InternalComm_ReqChannelCxtType;

/**
 * \brief 内网通信请求响应超时事件类型定义
 */
typedef struct{
    Async_EventType Event; /**< 响应超时事件 */
    InternalComm_ReqChannelCxtType *Cxt; /**< 超时通道指针 */
}InternalComm_AsyncEventType;


/**
 * \brief 内网通信数据发送获取发送数据回调函数类型定义
 */
typedef void (*InternalComm_GetSendDataFunc)(App_SlaveIdType SlaveNum, InternalComm_DidTypes Did, InternalComm_MsgType DataBufferPtr, InternalComm_MsgLenType *Length);


/**
 * \brief 内网通信消息上下文类型定义
 */
typedef struct _InternalComm_ReqChannelCxtType
{
    uint8 ChannelNum; /**< 当前通道编号 */
    InternalComm_DidTypes CurrentDid; /**< 当前DID值 */
    App_SlaveIdType CurrentSlave; /**< 当前从机号 */
    InternalComm_SlaveBitMaskType SlaveMaskBit; /**< 请求从机位掩码 */
    InternalComm_SlaveBitMaskType ChlSlaveMask; /**< 当前通道支持的从机的掩码 */
    RingBuffer_Type PendingDidRb; /**< Pending DID缓存 */

    uint8 SendDiagState; /**< 发送会话状态 */
    uint8 SendRetryCnt; /**< 发送重试 */
    InternalComm_MsgType SendDataPtr; /**< 发送缓存 */
    InternalComm_MsgLenType SendDataLen; /**< 发送数据长度 */
    InternalComm_MsgLenType AvailableSendDataLen; /**< 可用发送缓存 */
    InternalComm_GetSendDataFunc GetSendDataFunc; /**< 发送数据获取函数 */

    uint8 XgateFlag; /**< xgate使用接收缓存标志 */
    uint8 ReceiveErrorCnt; /**< 接收错误计数 */
    uint8 ReceiveDiagState; /**< 接收状态 */
    App_SlaveIdType ReceiveSlave; /**< 当前接收信息的从机号 */
    InternalComm_MsgType ReceiveDataPtr; /**< 接收缓存 */
    InternalComm_MsgLenType ReceiveDataLen; /**< 接收数据长度 */
    InternalComm_MsgLenType AvailableRecBufferSize; /**< 可用接收缓存大小 */
    InternalComm_AsyncEventType AsyncEvent; /**< 请求响应超时事件 */
}InternalComm_ReqChannelCxtType;

/**
 * \brief 内网通信DID读取调度表.
 */
typedef struct InternalComm_DIDReadScheduleItem {
    InternalComm_DidTypes DID; /**< 需要读取的DID. */
    uint16 Interval;  /**< 读取的间隔时间. */
    InternalComm_GetSendDataFunc GetSendDataFunc; /**< 获取发送数据函数 */
    Async_EventCbkType Request; /**< 请求DID回调函数. */
} InternalComm_ScheduleItemType;

/**
 * \brief 内网通信从机温感类型配置数据类型定义
 */
typedef struct{
    boolean IsFinish; /**< 温感类型配置是否完成 */
    uint16 SameFlag; /**< 从机温感类型相同标志 从机位域 */
}InternalComm_TempTypeCfgCxtType;

typedef void (*InternalComm_RecSlaveDataHook)(App_SlaveIdType SlaveId, uint8* const DataPtr, uint16 Length);

/**
 * \brief 内网通信基本配置类型定义
 */
typedef struct{
    InternalComm_RecSlaveDataHook recVoltHook; /**< 接收到电压数据钩子函数 */
    InternalComm_RecSlaveDataHook recTempHook; /**< 接收到温度数据钩子函数 */
}InternalComm_ConfigInfoType;

/**
 * \brief 内网通信发送Looper
 */
extern Async_LooperType InternalComm_TxLooper;

/**
 * \brief 内网通信消息上下文类型定义
 */
extern InternalComm_ReqChannelCxtType InternalComm_ReqChannelCxt[INTERNALCOMM_REQUIRE_CHANNEL_NUM];

#pragma push
#pragma DATA_SEG __GPAGE_SEG XGATE_DATA
#pragma CONST_SEG __GPAGE_SEG XGATE_CONST

/**
 * \brief 内网通信接收缓存定义
 */
extern InternalComm_MsgItemType InternalComm_RxMsgBuffer[INTERNALCOMM_REQUIRE_CHANNEL_NUM][INTERNALCOMM_RX_BUFF_SIZE];

/**
 * \内网通信从机通信中断标志 bitmap
 */
extern uint32 InternalComm_CommAbortFlag;

#pragma pop

/**
 * \brief 内网通信发送缓存定义
 */
extern InternalComm_MsgItemType InternalComm_TxMsgBuffer[INTERNALCOMM_REQUIRE_CHANNEL_NUM][INTERNALCOMM_TX_BUFF_SIZE];

/**
 * \brief 内网通信从机通信计时
 */
extern uint32 InternalComm_SlaveTick[BCU_SLAVE_NUM_MAX];

/**
 * \brief 内网通信从机通信超时位标记
 * \note 对应位置1，表示对应从机通信无响应，在非首个DID请求时自动过滤，以节省请求时间
 */
extern InternalComm_SlaveBitMaskType InternalComm_SlaveTimeoutBit;

/**
 * \brief 内网通信从机温感类型配置上下文
 */
extern InternalComm_TempTypeCfgCxtType InternalComm_TempTypeCfgCxt;

/**
 * \brief 内网通信向从机请求项
 */
extern const InternalComm_ScheduleItemType InternalComm_ScheduleItem[INTERNALCOMM_SLAVE_DID_NUM];

/**
 * \brief 内网通信请求通道转换为Xgate数据处理通道
 */
extern const uint8 InternalComm_ReqChannelToXgate[];

/**
 * \brief Xgate软件数据处理通道转换为内网通信请求通道
 */
extern const uint8 InternalComm_XgateSoftwareIsrChlToReq[];


/**
 * \brief 内网通信DID异步事件
 */
extern Async_EventType InternalComm_ScheduleItemEvent[INTERNALCOMM_SLAVE_DID_NUM];

extern InternalComm_DidTypes InternalComm_SlaveFirstDID;

extern const InternalComm_ConfigInfoType InternalComm_ConfigInfo;

extern uint8 InternalComm_TempTypeCfgCntBuff[];

extern InternalComm_SlaveBitMaskType InternalComm_DID0x488Bit;
extern InternalComm_SlaveBitMaskType InternalComm_DID0x48DBit;

/**
 * \brief 内网通信初始化
 *
 * \param pri 任务优先级
 */
void InternalComm_Init(uint8 pri);

/**
 * \brief 内网通信是否已启动
 * \return FALSE-未启动 TRUE-已启动
 */
boolean InternalComm_IsStart(void);

/**
 * \brief 内网通信模块上下文状态初始化
 */
void InternalComm_InternalInit(void);

/**
 * \brief 复位DID请求从机掩码位
 * \details 根据请求通道配置的起止初始化从机请求掩码位，如果当前从机通信超时位为真，对应从机掩码位将不被置位
 *
 * \param Context 请求通道上下文
 */
void InternalComm_InitSlaveMaskBit(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 复位发送状态信息
 *
 * \param Context 请求通道上下文
 */
void InternalComm_ResetSendStatus(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 复位接收状态信息
 *
 * \param Context 请求通道上下文
 */
void InternalComm_ResetReceiveStatus(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 复位接收状态信息
 *
 * \param Context 请求通道上下文
 */
void InternalComm_ResetReceiveStatusCarefully(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 更新当前可用的待请求的从机号
 *
 * \param Context 请求通道上下文
 * \return 从机号 返回-1表示无可用从机号
 */
App_SlaveIdType InternalComm_UpdateRequireSlaveId(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 更新当前可用的待请求的DID
 * \details 当前已请求的DID不为无效DID时直接返回，为无效DID，则从缓存中获取Pending DID
 *
 * \param Context 请求通道上下文
 * \return 获取到的DID值 返回-1表示可用DID
 */
InternalComm_DidTypes InternalComm_UpdateRequireDid(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 更新待请求从机及DID值
 * \details 如果当前DID值无效，分别更新DID值和从机号为有效值；如果仅从机号无效，则更新从机号，当此DID值所有从机请求结束，同时更新DID值。
 *
 * \param Context 请求通道上下文
 * \return E_OK:更新成功 E_NOT_OK:更新失败
 */
Std_ReturnType InternalComm_UpdateReqSlaveAndDid(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 向所有请求通道写入需请求的DID值
 * \details 如果请求通道空闲，直接写入发送DID缓存，并更新请求从机掩码，启动请求发送；如果不空闲，则将DID写入发送缓存；
 *          如果写入失败，会启动更新DID及从机号，然后启动请求发送。
 *
 * \param Did 待请求的DID
 * \param GetSendDataFunc 获取待发送数据的函数指针
 */
void InternalComm_AddRequireDid(InternalComm_DidTypes Did, InternalComm_GetSendDataFunc GetSendDataFunc);

/**
 * \brief 启动请求通道请求从机DID
 * \details 当前请求通道为空闲且DID值与从机号均有效时，启动从机对应DID数据请求。
 *
 * \param Context 请求通道上下文
 * \return E_OK:启动成功 E_NOT_OK:启动失败
 */
Std_ReturnType InternalComm_StartChannelRequire(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 重启请求通道请求从机DID
 * \details 重新启动从机对应DID数据请求。
 *
 * \param Context 请求通道上下文
 * \return E_OK:重启成功 E_NOT_OK:重启失败
 */
Std_ReturnType InternalComm_RestartChannelRequire(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 清除从机数据
 * \details 当出现通信中断时调用此函数清除对应从机的数据，包括电压、温度、板载电压、板载温度、均衡状态、HLSS状态等信息
 *
 * \param Context 请求通道上下文
 * \return E_OK:操作成功 E_NOT_OK:操作失败
 */
Std_ReturnType InternalComm_ClrSlaveData(const InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 清除当前通道状态并启动下一个从机请求
 *
 * \param Context 请求通道上下文
 * \return E_OK:操作成功 E_NOT_OK:操作失败
 */
Std_ReturnType InternalComm_ClrCurrentChlAndReqNext(InternalComm_ReqChannelCxtType *Context);

/**
 * \brief 内网通信是否有从机无通信检查
 *
 * \return 0-没有 1-有
 */
uint16 InternalComm_SlaveIsNoComm(void);

/**
 * \brief 从机温感类型是否有效
 * \details 当完成所有从机温感类型配置后，认为有效
 * \return FALSE-无效 TRUE-有效
 */
boolean InternalComm_SlaveRequireIsAllow(void);

/**
 * \brief 从机通信中断标志bitmap
 * \details 0-通信正常 1-通信中断 bit0-1号从机/一体机通信状态 bit1-2号从机通信状态 。。。
 * \return 从机通信bitmap
 */
uint32 InternalComm_GetSlaveCommAbortBitMap(void);



#endif

/** \} */

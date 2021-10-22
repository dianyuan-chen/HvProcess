/**
 * \file VcuComm_Internal.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 整车通信内部头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20180117 |
 */

/**
 * \addtogroup VcuComm 整车通信
 * \{
 */

#ifndef VCUCOMM_INTERNAL_H_
#define VCUCOMM_INTERNAL_H_


#include "ComStack_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

#define VCUCOMM_DEV_ERROR_DETECT            STD_OFF

#define VCUCOMM_LOOPER_CMD_BUFF_SIZE        200U
#define VCUCOMM_TX_TASK_STK_SIZE            400U

#define VCUCOMM_SEND_CMDT_BUFFER_SIZE       200U
#define VCUCOMM_REC_CMDT_BUFFER_SIZE        100U
#define VCUCOMM_DIRECT_BUFFER_SIZE          8U

#define VCUCOMM_ASYNC_EVENT_NUM             10U

/**
 * \RingBuffer size define
 */
#define VCUCOMM_SEND_CMDT_IPDU_BUFF_SIZE    50U
#define VCUCOMM_SEND_DIRECT_IPDU_BUFF_SIZE  125U

#define VCUCOMM_SEND_IPDU_ITEM_BUFF_SIZE    125U

/**
 * \brief 发送重试次数
 */
#define VCUCOMM_SEND_RETRY_NUM              2U

/**
 * \brief 发送事件类型
 */
#define VCUCOMM_EVENT_TYPE_IDLE             0U
#define VCUCOMM_EVENT_TYPE_SEND_NEXT_IPDU   0U
#define VCUCOMM_EVENT_TYPE_RESEND_IPDU      2U
#define VCUCOMM_EVENT_TYPE_WAIT_CONFIRM     3U


#define VCUCOMM_DATA_LENGTH_NOT_FIX         0xFFFFU

#define VCUCOMM_MONITOR_REC_MSG_NUM_PER_STAGE   10U
#define VCUCOMM_REC_TRIGGER_RECEIVE_DATA    0x80U

#define VCUCOMM_REC_TIMEOUT_DEFAULT         5000U

#define VCUCOMM_INVALID_IPDU                0xFFU

/**
 * \brief 整车通信数据发送回调函数类型定义
 */
typedef void (*VcuCommSendFuncCbk)(uint8 *dataPtr, uint16 *Length);

/**
 * \brief 发送条件检查函数类型定义
 */
typedef Std_ReturnType (*VcuCommSendCondCheckFunc)(uint16 IPdu);

/**
 * \brief 整车通信数据接收回调函数类型定义
 */
typedef void (*VcuCommRecFuncCbk)(uint8 *dataPtr, uint16 Length);

/**
 * \brief 获取接收报文超时参数
 *
 * \return 超时时间
 */
typedef uint16 (*VcuCommGetRecIPduTimeout)(void);

/**
 * \brief 整车通信报文接收超时回调函数类型定义
 */
typedef void (*VcuCommRecTimeoutCbk)(void);

/**
 * \brief 整车通信发送Ipdu配置类型定义
 */
typedef struct{
    uint16 IPdu; /**< 发送IPdu */
    uint16 Length; /**< 发送数据长度 */
    uint16 Cycle; /**< 数据发送周期 */
    VcuCommSendCondCheckFunc CondFunc; /**< 发送条件检查函数 */
    VcuCommSendFuncCbk Func; /**< 数据发送回调函数 */
}VcuComm_SendIPduCfgType;

/**
 * \brief 整车通信接收Ipdu信息类型定义
 */
typedef struct{
    uint16 IPdu; /**< 接收IPdu */
    uint16 Length; /**< 数据长度 */
    uint16 Timeout; /**< 超时时间 */
    VcuCommGetRecIPduTimeout TimeoutFunc; /**< 获取IPdu超时时间回调函数，当此函数有效时，Timeout配置参数无效 */
    VcuCommRecFuncCbk RecFunc; /**< 数据接收回调函数 */
    VcuCommRecTimeoutCbk TimeoutEventFunc; /**< 数据接收超时事件回调函数 */
}VcuComm_RecIPduInfoType;

/**
 * \brief 整车通信接收IPdu配置类型定义
 */
typedef struct{
    uint8 IPduNum; /**< IPdu个数 */
    const VcuComm_RecIPduInfoType *IPduInfo; /**< 各IPdu配置信息 */
}VcuComm_RecIPduCfgType;


/**
 * \brief 整车通信状态类型定义
 */
typedef enum{
    VCUCOMM_COMM_STATE_IDLE,
    VCUCOMM_COMM_STATE_SENDING,
    VCUCOMM_COMM_STATE_SENDING_CONFIG,
    VCUCOMM_COMM_STATE_RECEIVING,
    VCUCOMM_COMM_STATE_INDICATION,
    VCUCOMM_COMM_STATE_PROCESSING,
}VcuComm_CommStateType;

/**
 * \brief 整车通信发送数据信息类型定义
 */
typedef struct{
    uint16 IPdu; /**< 当前IPdu */
    const VcuComm_SendIPduCfgType *Cfg; /**< IPdu配置 */
    uint8 *Buffer; /**< 数据缓存 */
    uint16 Length; /**< 数据发送长度 */
    uint16 AvailableSize; /**< 可用发送数据长度 */
    uint8 RetryCnt; /**< 发送重试计数 */
    VcuComm_CommStateType State; /**< 状态 */
    RingBuffer_Type Rb; /**< IPdu缓存 */
    Async_EventType Event; /**< 延时发送事件 */
}VcuComm_SendHandleType;

/**
 * \brief 整车通信接收数据信息类型定义
 */
typedef struct{
    uint16 IPdu; /**< 当前IPdu */
    uint8 *Buffer; /**< 数据缓存 */
    uint16 Length; /**< 接收数据长度 */
    uint16 AvailableSize; /**< 可用数据长度 */
    VcuComm_CommStateType State; /**< 状态 */
}VcuComm_RecHandleType;

/**
 * \brief 整车通信发送条目相关数据链表项类型
 */
typedef struct {
    struct list_head list; //!< 双向链表表头
    const VcuComm_SendIPduCfgType *Cfg; /**< IPdu配置 */
}VcuComm_SendInfoItemType;

/**
 * \brief 整车通信发送异步事件类型定义
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    struct list_head head; /**< 事件动作链表，用于链接发送IPdu Cfg */
}VcuComm_SendAsyncEventType;

/**
 * \brief 整车通信接收异步事件类型定义
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    uint8 index; /**< 事件索引号 */
}VcuComm_RecAsyncEventType;

typedef struct{
    boolean StartFlag; /**< 启动标志 */
    uint16 CurrentRecStage; /**< 接收阶段 */
    uint16 NewRecStage; /**< 用于等待阶段切换完成 */
    VcuComm_SendHandleType SendCmdtHandle; /**< Cmdt发送句柄 */
    VcuComm_SendHandleType SendDirectHandle; /**< Direct发送句柄 */
    VcuComm_RecHandleType RecCmdtHandle; /**< Cmdt接收句柄 */
    VcuComm_RecHandleType RecDirectHandle; /**< Direct接收句柄 */
    VcuComm_RecAsyncEventType RecEvents[VCUCOMM_MONITOR_REC_MSG_NUM_PER_STAGE];
    uint32 WriteRBFaultCnt; /**< 写RB错误计数 */
}VcuComm_InnerDataType;

extern const uint8 VcuComm_SendIPduNum;
extern const VcuComm_SendIPduCfgType VcuComm_IPduSendConfigInfo[];
extern const VcuComm_RecIPduCfgType VcuComm_IPduRecConfigInfo[];
extern const uint16 VcuComm_RxIPduStart;
extern const uint16 VcuComm_RxIPduStop;
extern const uint16 VcuComm_StageIdle;
extern const uint16 VcuComm_StageStart;
extern const uint16 VcuComm_StageStop;
extern const uint16 VcuComm_StageMax;

/**
 * @brief 整车通信发送IPDU报文注册
 *
 * @param StartConfigPtr 起始IPDU报文配置指针
 * @param length IPDU报文个数
 *
 * @return E_OK: 注册成功 E_NOT_OK: 注册失败
 */
Std_ReturnType VcuComm_SendIPduRegister(const VcuComm_SendIPduCfgType *StartConfigPtr, uint8 length);

/**
 * \brief 整车通信获取可用的发送句柄
 * \details 根据传入的数据长度确定是使用CMDT发送还是DIRECT发送，如果对应发送句柄空闲，则返回对应发送句柄，否则返回NULL
 *
 * \param Length 待发送数据长度
 * \return 发送句柄
 */
VcuComm_SendHandleType* VcuComm_GetFreeSendHandle(uint16 Length);

/**
 * \brief 根据长度获取发送句柄
 * \details 根据输入的数据长度获取此数据需要发送的发送句柄，此函数不关心此发送句柄是否空闲，直接返回对应发送句柄
 *
 * \param Length 数据长度
 * \return 发送句柄
 */
VcuComm_SendHandleType* VcuComm_GetSendHandle(uint16 Length);

/**
 * \brief 整车通信获取可用的接收句柄
 * \details 根据传入的数据长度确定是使用CMDT接收还是DIRECT接收，如果对应接收句柄空闲，则返回对应接收句柄，否则返回NULL
 *
 * \param Length 待接收数据长度
 * \return 接收句柄
 */
VcuComm_RecHandleType* VcuComm_GetFreeRecHandle(uint16 IPdu, uint16 Length);

/**
 * \brief 整车通信初始化发送句柄
 * \details 初始化handle中的相关发送参数，参见\link VcuComm_SendHandleType \endlink定义
 *
 * \param IPdu IPdu编号
 * \param handle 报文发送句柄
 * \param cfg 报文配置指针
 */
void VcuComm_InitSendHandle(VcuComm_SendHandleType *handle, const VcuComm_SendIPduCfgType *cfg);

/**
 * \brief 获取与输入IPdu的相同发送句柄
 * \details 查找与输入IPdu相同值的发送句柄，返回NULL表示无相同IPdu的发送句柄
 *
 * \param IPdu 整车通信IPdu编号
 * \return 发送句柄
 */
VcuComm_SendHandleType* VcuComm_GetIPduSendHandle(uint16 IPdu);

/**
 * \brief 获取与接收IPdu相同的接收句柄
 * \details 查找与输入IPdu相同值的接收句柄，返回NULL表示无相同IPdu的接收句柄
 *
 * \param IPdu 整车通信IPdu编号
 * \return 接收句柄
 */
VcuComm_RecHandleType* VcuComm_GetIPduRecHandle(uint16 IPdu);

/**
 * \brief 根据IPdu编号发送对应的IPdu数据
 *
 * \param IPdu 整车通信IPdu编号
 * \param send_type 0-新IPdu 1-缓存IPdu
 * \return E_OK: 发送成功 E_NOT_OK: 发送失败
 */
Std_ReturnType VcuComm_SendIPduData(uint16 IPdu, uint8 send_type);

/**
 * \brief 重新发送IPdu对应的数据
 * \details 当出现发送失败时，可通过此函数重启发送
 *
 * \param handle 发送句柄
 * \return E_OK: 重启成功 E_NOT_OK: 重启失败
 */
Std_ReturnType VcuComm_ReSendIPduData(VcuComm_SendHandleType *handle);

/**
 * \brief 发送被写入RB中的IPdu数据
 * \details 从发送句柄的RB中获取未成功发送的IPdu，并发送其数据
 *
 * \param handle 发送句柄
 * \return E_OK: 成功 E_NOT_OK: 失败
 */
Std_ReturnType VcuComm_SendNextIPduData(VcuComm_SendHandleType *handle);

/**
 * \brief 检查是否允许发送重试
 *
 * \param handle 发送句柄
 * \return TRUE: 允许 FALSE: 不允许
 */
uint8 VcuComm_SendRetryIsAllow(const VcuComm_SendHandleType *handle);

/**
 * \brief 读取上层待发送数据到TP层缓存
 * \details 从发送缓存读取发送数据，并更新未发送数据缓存指针及长度信息
 *
 * \param CanTxPduId 发送PduId
 * \param PduInfoPtr Pdu数据指针
 * \param length 读取长度，返回剩余长度
 * \return 缓存大小请求结果
 */
BufReq_ReturnType VcuComm_ReadTxData(PduIdType CanTxPduId, const PduInfoType *const PduInfoPtr, PduLengthType *length);

/**
 * \brief 将从TP层接收到的数据写入上层接收缓存
 * \details 将从TP层接收到的数据写入上层的接收缓存，并更新上层接收缓存指针及长度信息
 *
 * \param CanRxPduId 接收PduId
 * \param PduInfoPtr Pdu数据指针
 * \param length 接收数据长度,返回上层缓存剩余可用长度
 * \return 缓存大小请求结果
 */
BufReq_ReturnType VcuComm_WriteRxData(PduIdType CanRxPduId, const PduInfoType *const PduInfoPtr, PduLengthType *length);

/**
 * \brief 复位接收缓存信息
 * \details 复位接收缓存指针及缓存大小值
 *
 * \param handle 接收句柄
 */
void VcuComm_ResetRecBuffer(VcuComm_RecHandleType *handle);

/**
 * \brief 获取当前接收阶段的配置信息
 *
 * \param stage 接收阶段
 * \return 配置信息 返回NULL表示无可用配置
 */
const VcuComm_RecIPduCfgType* VcuComm_GetRecStageCfg(uint16 stage);

/**
 * \brief 从当前接收阶段查找IPdu的配置信息
 *
 * \param IPdu 整车通信IPdu编号
 * \return IPdu相关信息 返回NULL表示无可用信息
 */
const VcuComm_RecIPduInfoType* VcuComm_GetRecIPduInfo(uint16 IPdu);

/**
 * \brief 整车通信设置接收状态为空闲阶段
 */
void VcuComm_SetRecIdleStage(uint8 channel);

/**
 * \brief 启动新的接收阶段超时计时
 * \details 根据传入的接收阶段stage启动对应的所有接收报文的超时计时
 *
 * \param channel 通道号
 * \param currentStage 接收阶段
 */
void VcuComm_StartRecStageTimeout(uint8 channel, uint16 currentStage);

/**
 * \brief 整车通信触发接收阶段切换事件
 *
 * \param stage 新接收阶段
 */
void VcuComm_TriggerNewRecStage(uint16 stage);


/**
 * \brief 获取发送Cmdt数据句柄
 *
 * \return 发送句柄
 */
VcuComm_SendHandleType* VcuComm_GetSendCmdtHandle(void);

/**
 * \brief 获取发送Direct数据句柄
 *
 * \return 发送句柄
 */
VcuComm_SendHandleType* VcuComm_GetSendDirectHandle(void);

/**
 * \brief 设置当前整车通信接收阶段
 *
 * \param stage 接收阶段
 */
void VcuComm_SetCurrentRecStage(uint16 stage);

/**
 * \brief 获取整车通信正在进入的接收阶段
 *
 * \return 接收阶段
 */
uint16 VcuComm_GetTriggerNewRecStage(void);

/**
 * \brief 设置当前整车需要进入的接收阶段
 *
 * \param stage 接收阶段
 */
void VcuComm_SetTriggerNewRecStage(uint16 stage);

/**
 * \brief 根据IPdu编号获取对应的异步接收超时事件
 *
 * \param IPdu IPdu编号
 * \return 异步超时事件指针 NULL表示为空
 */
VcuComm_RecAsyncEventType* VcuComm_GetRecAsyncEvent(uint16 IPdu);

/**
 * \brief 获取当前整车通信接收阶段
 *
 * \return 接收阶段
 */
uint16 VcuComm_GetCurrentRecStage(void);

/**
 * \brief 获取接收异步事件指针
 *
 * \return 接收异步事件指针
 */
VcuComm_RecAsyncEventType* VcuComm_GetRecAsyncEventPtr(void);


#endif

/**
 * \}
 */


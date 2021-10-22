/**
 * \file ChargerComm.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电机通信内部头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20180212 |
 */

/**
 * \addtogroup ChargerComm 充电机通信
 * \{
 */


#ifndef CHARGERCOMM_INTERNAL_H_
#define CHARGERCOMM_INTERNAL_H_

#include "Async_Looper.h"
#include "Async_Event.h"
#include "ComStack_Types.h"
#include "ChargerComm_Types.h"

#define CHARGERCOMM_DEV_ERROR_DETECT        STD_OFF

#define CHARGERCOMM_LOOPER_CMD_BUFF_SIZE    200U
#define CHARGERCOMM_TX_TASK_STK_SIZE        400U

#define CHARGERCOMM_SEND_CMDT_BUFFER_SIZE   820U
#define CHARGERCOMM_REC_CMDT_BUFFER_SIZE    50U
#define CHARGERCOMM_DIRECT_BUFFER_SIZE      8U

#define CHARGERCOMM_ASYNC_EVENT_NUM         10U

//发送事件类型
#define CHARGERCOMM_EVENT_TYPE_IDLE                 0U
#define CHARGERCOMM_EVENT_TYPE_SEND_NEXT_IPDU       1U
#define CHARGERCOMM_EVENT_TYPE_RESEND_IPDU          2U
#define CHARGERCOMM_EVENT_TYPE_WAIT_CONFIRM         3U

/**
 * \RingBuffer size define
 */
#define CHARGERCOMM_SEND_CMDT_IPDU_BUFF_SIZE    50U
#define CHARGERCOMM_SEND_DIRECT_IPDU_BUFF_SIZE  50U

#define CHARGERCOMM_CHR_FAULT_USE_BIT_NUM       2U
#define CHARGERCOMM_CHR_FAULT_MASK_NUM          3U
#define CHARGERCOMM_CHR_FAULT_NUM_IN_BYTE       (8U/CHARGERCOMM_CHR_FAULT_USE_BIT_NUM)
#define CHARGERCOMM_CHR_FAULT_STATUS_BUFF_NUM   ((((uint16)CHARGERCOMM_CHR_FAULT_INDEX_MAX+CHARGERCOMM_CHR_FAULT_NUM_IN_BYTE)-1U)/CHARGERCOMM_CHR_FAULT_NUM_IN_BYTE)
#define CHARGERCOMM_CHR_FAULT_STATUS_DEFAULT    0xFFU

#define CHARGERCOMM_INVALID_IPDU                0xFFU

typedef uint8 ChargerComm_IPduType;

/**
 * \brief 充电机通信状态类型定义
 */
typedef enum{
    CHARGERCOMM_COMM_STATE_IDLE,
    CHARGERCOMM_COMM_STATE_SENDING,
    CHARGERCOMM_COMM_STATE_SENDING_CONFIG,
    CHARGERCOMM_COMM_STATE_RECEIVING,
    CHARGERCOMM_COMM_STATE_INDICATION,
    CHARGERCOMM_COMM_STATE_PROCESSING,
}ChargerComm_CommStateType;


/**
 * \brief 充电机通信发送数据信息类型定义
 */
typedef struct{
    ChargerComm_IPduType IPdu; /**< 当前IPdu */
    const ChargerComm_SendIPduCfgType *Cfg; /**< IPdu配置 */
    uint8 *Buffer; /**< 数据缓存 */
    uint16 Length; /**< 数据发送长度 */
    uint16 AvailableSize; /**< 可用发送数据长度 */
    uint8 RetryCnt; /**< 发送重试计数 */
    ChargerComm_CommStateType State; /**< 状态 */
    RingBuffer_Type Rb; /**< IPdu缓存 */
    Async_EventType Event; /**< 延时发送事件 */
}ChargerComm_SendHandleType;

/**
 * \brief 充电机通信接收数据信息类型定义
 */
typedef struct{
    ChargerComm_IPduType IPdu; /**< 当前IPdu */
    uint8 *Buffer; /**< 数据缓存 */
    uint16 Length; /**< 接收数据长度 */
    uint16 AvailableSize; /**< 可用数据长度 */
    ChargerComm_CommStateType State; /**< 状态 */
}ChargerComm_RecHandleType;

/**
 * \brief 充电机通信发送条目相关数据链表项类型
 */
typedef struct {
    struct list_head list; //!< 双向链表表头
    const ChargerComm_SendIPduCfgType *Cfg; /**< IPdu配置 */
}ChargerComm_SendInfoItemType;

/**
 * \brief 充电机通信发送异步事件类型定义
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    struct list_head head; /**< 事件动作链表，用于链接发送IPdu Cfg */
}ChargerComm_SendAsyncEventType;

/**
 * \brief 充电机通信接收异步事件类型定义
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    uint8 index; /**< 事件索引号 */
}ChargerComm_RecAsyncEventType;

typedef struct{
    boolean StartFlag; /**< 启动标志 */
    ChargerComm_StageType CurrentRecStage; /**< 接收阶段 */
    ChargerComm_StageType NewRecStage; /**< 用于等待阶段切换完成 */
    ChargerComm_SendHandleType SendCmdtHandle; /**< Cmdt发送句柄 */
    ChargerComm_SendHandleType SendDirectHandle; /**< Direct发送句柄 */
    ChargerComm_RecHandleType RecCmdtHandle; /**< Cmdt接收句柄 */
    ChargerComm_RecHandleType RecDirectHandle; /**< Direct接收句柄 */
    ChargerComm_RecAsyncEventType RecEvents[CHARGERCOMM_MONITOR_REC_MSG_NUM_PER_STAGE];
}ChargerComm_InnerDataType;

extern const uint8 ChargerComm_SendIPduNum;
extern const uint8 ChargerComm_RecIPduNum;
extern const ChargerComm_RecIPduCfgType ChargerComm_IPduRecConfigInfo[];
extern const ChargerComm_ConfigType ChargerComm_ConfigInfo;

/**
 * \brief 充电机通信报文发送事件注册
 *
 * \param StartConfigPtr 待发送报文的起始配置指针
 * \param length 待发送报文的个数
 *
 * \return E_OK: 注册成功 E_NOT_OK: 注册未成功
 */
Std_ReturnType ChargerComm_SendIPduRegister(const ChargerComm_SendIPduCfgType* StartConfigPtr, uint8 length);

/**
 * \brief 充电机通信获取可用的发送句柄
 * \details 根据传入的数据长度确定是使用CMDT发送还是DIRECT发送，如果对应发送句柄空闲，则返回对应发送句柄，否则返回NULL
 *
 * \param IPdu IPdu编号
 * \param Length 待发送数据长度
 * \return 发送句柄
 */
ChargerComm_SendHandleType* ChargerComm_GetFreeSendHandle(ChargerComm_IPduType IPdu, uint16 Length);

/**
 * \brief 根据长度获取发送句柄
 * \details 根据输入的数据长度获取此数据需要发送的发送句柄，此函数不关心此发送句柄是否空闲，直接返回对应发送句柄
 *
 * \param Length 数据长度
 * \return 发送句柄
 */
ChargerComm_SendHandleType* ChargerComm_GetSendHandle(uint16 Length);

/**
 * \brief 充电机通信获取可用的接收句柄
 * \details 根据传入的数据长度确定是使用CMDT接收还是DIRECT接收，如果对应接收句柄空闲，则返回对应接收句柄，否则返回NULL
 *
 * \param Length 待接收数据长度
 * \return 接收句柄
 */
ChargerComm_RecHandleType* ChargerComm_GetFreeRecHandle(ChargerComm_IPduType IPdu, uint16 Length);

/**
 * \brief 充电机通信初始化发送句柄
 * \details 初始化handle中的相关发送参数，参见\link ChargerComm_SendHandleType \endlink定义
 *
 * \param IPdu IPdu编号
 * \param handle 报文发送句柄
 * \param cfg 报文配置指针
 */
void ChargerComm_InitSendHandle(ChargerComm_SendHandleType *handle, const ChargerComm_SendIPduCfgType *cfg);

/**
 * \brief 获取与输入IPdu的相同发送句柄
 * \details 查找与输入IPdu相同值的发送句柄，返回NULL表示无相同IPdu的发送句柄
 *
 * \param IPdu 充电机通信IPdu编号
 * \return 发送句柄
 */
ChargerComm_SendHandleType* ChargerComm_GetIPduSendHandle(ChargerComm_IPduType IPdu);

/**
 * \brief 获取与接收IPdu相同的接收句柄
 * \details 查找与输入IPdu相同值的接收句柄，返回NULL表示无相同IPdu的接收句柄
 *
 * \param IPdu 充电机通信IPdu编号
 * \return 接收句柄
 */
ChargerComm_RecHandleType* ChargerComm_GetIPduRecHandle(ChargerComm_IPduType IPdu);

/**
 * \brief 根据IPdu编号发送对应的IPdu数据
 *
 * \param IPdu 充电机通信IPdu编号
 * \return E_OK: 发送成功 E_NOT_OK: 发送失败
 */
Std_ReturnType ChargerComm_SendIPduData(ChargerComm_IPduType IPdu);

/**
 * \brief 重新发送IPdu对应的数据
 * \details 当出现发送失败时，可通过此函数重启发送
 *
 * \param handle 发送句柄
 * \return E_OK: 重启成功 E_NOT_OK: 重启失败
 */
Std_ReturnType ChargerComm_ReSendIPduData(ChargerComm_SendHandleType *handle);

/**
 * \brief 发送被写入RB中的IPdu数据
 * \details 从发送句柄的RB中获取未成功发送的IPdu，并发送其数据
 *
 * \param handle 发送句柄
 */
void ChargerComm_SendNextIPduData(ChargerComm_SendHandleType *handle);

/**
 * \brief 检查是否允许发送重试
 *
 * \param handle 发送句柄
 * \return TRUE: 允许 FALSE: 不允许
 */
uint8 ChargerComm_SendRetryIsAllow(const ChargerComm_SendHandleType *handle);

/**
 * \brief 读取上层待发送数据到TP层缓存
 * \details 从发送缓存读取发送数据，并更新未发送数据缓存指针及长度信息
 *
 * \param CanTxPduId 发送PduId
 * \param PduInfoPtr Pdu数据指针
 * \param length 读取长度，返回剩余长度
 * \return 缓存大小请求结果
 */
BufReq_ReturnType ChargerComm_ReadTxData(PduIdType CanTxPduId, const PduInfoType *const PduInfoPtr, PduLengthType *length);

/**
 * \brief 将从TP层接收到的数据写入上层接收缓存
 * \details 将从TP层接收到的数据写入上层的接收缓存，并更新上层接收缓存指针及长度信息
 *
 * \param CanRxPduId 接收PduId
 * \param PduInfoPtr Pdu数据指针
 * \param length 接收数据长度,返回上层缓存剩余可用长度
 * \return 缓存大小请求结果
 */
BufReq_ReturnType ChargerComm_WriteRxData(PduIdType CanRxPduId, const PduInfoType *const PduInfoPtr, PduLengthType *length);

/**
 * \brief 复位接收缓存信息
 * \details 复位接收缓存指针及缓存大小值
 *
 * \param handle 接收句柄
 */
inline void ChargerComm_ResetRecBuffer(ChargerComm_RecHandleType *handle);

/**
 * \brief 获取当前接收阶段的配置信息
 *
 * \param stage 接收阶段
 * \return 配置信息 返回NULL表示无可用配置
 */
const ChargerComm_RecIPduCfgType* ChargerComm_GetRecStageCfg(ChargerComm_StageType stage);

/**
 * \brief 从当前接收阶段查找IPdu的配置信息
 *
 * \param IPdu 充电机通信IPdu编号
 * \return IPdu相关信息 返回NULL表示无可用信息
 */
const ChargerComm_RecIPduInfoType* ChargerComm_GetRecIPduInfo(ChargerComm_IPduType IPdu);

/**
 * \brief 充电机通信设置接收状态为空闲阶段
 */
void ChargerComm_SetRecIdleStage(uint8 channel);

/**
 * \brief 充电机通信触发接收阶段切换事件
 *
 * \param stage 新接收阶段
 */
inline void ChargerComm_TriggerNewRecStage(ChargerComm_StageType stage);


/**
 * \brief 获取发送Cmdt数据句柄
 *
 * \return 发送句柄
 */
inline ChargerComm_SendHandleType* ChargerComm_GetSendCmdtHandle(void);

/**
 * \brief 获取发送Direct数据句柄
 *
 * \return 发送句柄
 */
inline ChargerComm_SendHandleType* ChargerComm_GetSendDirectHandle(void);

/**
 * \brief 获取当前充电机通信接收阶段
 *
 * \return 接收阶段
 */
inline ChargerComm_StageType ChargerComm_GetCurrentRecStage(void);

/**
 * \brief 设置当前充电机通信接收阶段
 *
 * \param stage 接收阶段
 */
inline void ChargerComm_SetCurrentRecStage(ChargerComm_StageType stage);

/**
 * \brief 获取充电机通信正在进入的接收阶段
 *
 * \return 接收阶段
 */
inline ChargerComm_StageType ChargerComm_GetTriggerNewRecStage(void);

/**
 * \brief 设置当前充电机需要进入的接收阶段
 *
 * \param stage 接收阶段
 */
inline void ChargerComm_SetTriggerNewRecStage(ChargerComm_StageType stage);

/**
 * \brief 获取接收异步事件指针
 *
 * \return 接收异步事件指针
 */
ChargerComm_RecAsyncEventType* ChargerComm_GetRecAsyncEventPtr(void);

/**
 * \brief 根据IPdu编号获取对应的异步接收超时事件
 *
 * \param IPdu IPdu编号
 * \return 异步超时事件指针 NULL表示为空
 */
ChargerComm_RecAsyncEventType* ChargerComm_GetRecAsyncEvent(ChargerComm_IPduType IPdu);

/**
 * @brief 外部函数接口声明
 */
extern void ChargerCommGB_ChargerEnable(void);
extern void ChargerCommGB_ChargerDisable(void);
extern uint8 ChargerCommGB_IsCommunication(void);
extern uint8 ChargerCommGB_CheckChargeReq(uint16 delay);
extern uint8 ChargerCommGB_ChargeIsFaultStop(void);
extern Std_ReturnType ChargerCommUser_ChargeIsAllowed(void);

extern void ChargerCommUser_ChargerEnable(void);
extern void ChargerCommUser_ChargerDisable(void);
extern uint8 ChargerCommUser_IsCommunication(void);

extern void ExternCanCommGB_ChargerEnable(void);
extern void ExternCanCommGB_ChargerDisable(void);
extern uint8 ExternCanCommGB_IsCommunication(void);



#endif

/**
 * \}
 */
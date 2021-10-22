/**
 * \file PrechargeM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 预充电管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170427 |
 */

/**
 * \addtogroup Precharge 预充管理
 * \{
 */

#ifndef PRECHARGEM_H_
#define PRECHARGEM_H_

#include "App_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "PrechargeM_Cfg.h"
#include "CurrentM.h"

/**
 * \brief 预充状态类型定义
 */
typedef enum{
    PRECHARGEM_STATUS_NO_PRECHARGE, /**< 未预充 */
    PRECHARGEM_STATUS_PRECHARGE_RELAY_ON, /**< 预充继电器闭合 */
    PRECHARGEM_STATUS_PRECHARGE_RETRY_WAITING, /**< 等待重新预充 */
    PRECHARGEM_STATUS_PRECHARGING, /**< 预充中 */
    PRECHARGEM_STATUS_WAITING_MAIN_ON, /**< 等待主回路闭合 */
    PRECHARGEM_STATUS_PRECHARGE_FINISH, /**< 预充成功 */
    PRECHARGEM_STATUS_PRECHARGE_FAILURE, /**< 预充失败 */
    PRECHARGEM_STATUS_MAX,
}PrechargeM_StatusType;

/**
 * \brief 获取MCU端总压接口类型定义
 */
typedef App_Tv100mvType (*PrechargeM_GetMcuVoltageFunc)(void);

typedef enum{
    PRECHARGEM_FINISH_TYPE_DELTA_VOLT, /**< 压差值类型 */
    PRECHARGEM_FINISH_TYPE_PERCENT, /**< 百分比类型 */
    PRECHARGEM_FINISH_TYPE_DELAY, /**< 延时类型 */
}PrechargeM_FinishType;

typedef struct{
    PrechargeM_FinishType type; /**< 预充完成条件类型 */
    uint16 value; /**< 预充完成值 */
    Current_CurrentType current; /**< 完成电流值(0.1A) */
}PrechargeM_FinishCondType;

/**
 * \brief 预充配置参数类型
 */
typedef struct{
    uint8 retryNum; /**< 重试次数 */
    uint16 retryInternal; /**< 预充失败后重试间隔(ms) */
    uint16 timeMin; /**< 最小预充时间(ms) */
    uint16 timeout; /**< 预充超时时间(ms) */
    App_Tv100mvType validVoltMin; /**< 最低有效电压 */
    PrechargeM_FinishCondType finishCond; /**< 预充完成条件定义 */
    PrechargeM_GetMcuVoltageFunc getMcuVoltFunc; /**< 获取MCU总压接口 */
    uint16 continuousTime; /**< 预充完成持续时间(ms) */
    uint16 relayOnTimeout; /**< 预充继电器闭合超时(ms) */
    uint16 relayOffDelay; /**< 预充继电器断开延时，用于放电闭合后预充延时断开(ms) */
    uint16 dchgRelayOnTimeout; /**< 放电继电器闭合超时(ms) */
    uint8 prechargeRelayChannel; /**< 预充继电器通道号 */
    uint8 dchgRelayChannel; /**< 放电继电器通道号 */
    Current_CurrentType currentMax; /**< 预充最大安全电流(0.1A) */
    uint32 overCurTime; /**< 允许超预充最大电流最大时间(ms) */
}PrechargeM_ConfigInfoType;

typedef struct {
    uint8 start; /**< 预充启动标志 */
    uint8 retryCnt; /**< 重试计数 */
    uint32 timeoutTick; /**< 超时计时 */
    uint32 finishTick; /**< 预充完成计时 */
    uint32 overCurTick; /**< 预充过流计时 */
    PrechargeM_StatusType status; /**< 预充状态 */
}PrechargeM_ContextType;

/**
 * \brief 预充管理模块内部参数类型
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    PrechargeM_ContextType ctx[PRECHARGEM_MODE_NUM]; /**< 预充控制上下文信息 */
}PrechargeM_InnerDataType;

extern const PrechargeM_ConfigInfoType PrechargeM_ConfigInfo[];
extern const uint8 PrechargeM_ConfigInfoSize;

/**
 * \brief 预充管理模块初始化
 */
void PrechargeM_Init(Async_LooperType *looper);

/**
 * \brief 启动放电模式预充
 */
void PrechargeM_Start(void);

/**
 * \brief 停止放电模式预充
 */
void PrechargeM_Stop(void);

/**
 * \brief 复位放电模式预充
 */
void PrechargeM_Reset(void);

/**
 * \brief 放电模式预充是否已经启动
 * \return TRUE-启动 FALSE-未启动
 */
uint8 PrechargeM_IsStart(void);

/**
 * \brief 放电模式预充是否完成
 * \details 包含预充条件成立后，等待主回路继电器闭合而后断开预充
 *
 * \return TRUE-完成 FALSE-未完成
 */
uint8 PrechargeM_IsFinish(void);

/**
 * \brief 放电模式预充是否失败
 * \return TRUE-失败 FALSE-未失败
 */
uint16 PrechargeM_IsFailure(void);

/**
 * \brief 放电模式预充是否进行中
 * \details 预充失败重试等待过程中也认为未预充
 *
 * \return TRUE-预充中 FALSE-未预充
 */
uint8 PrechargeM_IsPrecharging(void);

/**
 * \brief 启动充电模式预充
 */
void PrechargeM_ChgStart(void);

/**
 * \brief 停止充电模式预充
 */
void PrechargeM_ChgStop(void);

/**
 * \brief 复位充电模式预充
 */
void PrechargeM_ChgReset(void);

/**
 * \brief 充电模式预充是否已经启动
 * \return TRUE-启动 FALSE-未启动
 */
uint8 PrechargeM_ChgIsStart(void);

/**
 * \brief 充电模式预充是否完成
 * \details 包含预充条件成立后，等待主回路继电器闭合而后断开预充
 *
 * \return TRUE-完成 FALSE-未完成
 */
uint8 PrechargeM_ChgIsFinish(void);

/**
 * \brief 充电模式预充是否失败
 * \return TRUE-失败 FALSE-未失败
 */
uint16 PrechargeM_ChgIsFailure(void);

/**
 * \brief 充电模式预充是否进行中
 * \details 预充失败重试等待过程中也认为未预充
 *
 * \return TRUE-预充中 FALSE-未预充
 */
uint8 PrechargeM_ChgIsPrecharging(void);

/**
 * \brief 预充是否失败
 * \details 根据充放电模式确认对应模式下预充是否失败，用于故障诊断模式
 * \return TRUE-失败 FALSE-未失败
 */
uint16 PrechargeM_DiagIsFailure(void);

#endif

/**
 * \}
 */
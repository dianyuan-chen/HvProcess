/**
 * \file UserStrategy.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 用户策略定义头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170322 |
 */
#ifndef USER_STRATEGY_H_
#define USER_STRATEGY_H_

#include "App_Types.h"
#include "PwmCapture.h"
#include "CurrentM.h"
#include "RelayM_Cfg.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "RuntimeM.h"

/**
 * \brief Error detect define
 */
#define USERSTRATEGY_DEV_ERROR_DETECT   STD_OFF

#define USERSTRATEGY_E_PARAM_INVALID_PTR            0x00U

#define USERSTRATEGY_BUZZER_LEVEL2_ON_TIME          1000U
#define USERSTRATEGY_BUZZER_LEVEL2_OFF_TIME         1000U

/**
 * \brief 用户自定义策略内部数据类型
 */
typedef struct{
    Async_EventType event; /**< 异步事件 */
    uint32 powerOffTick; /**< 下电计时 */
    boolean currentIsAllowToPowerOff; /**< 电流是否允许下电 */
}UserStrategy_InnerDataType;

/**
 * \brief 用户策略初始化
 */
void UserStrategy_Init(Async_LooperType *looper);

/**
 * \brief 用户策略是否允许安全下电条件检查
 * \return TRUE-允许 FALSE-不允许
 */
boolean UserStrategy_IsSafeToOff(void);

/**
 * \brief 国标充电机充电是否允许
 * \details 用户自定义策略控制国标充电进入充电准备就绪状态
 * \return TRUE-允许 FALSE-禁止
 */
boolean UserStartegy_ChargeIsAllow(void);

/**
 * \brief 获取充电机充电最大允许充电总压
 * \return 最大允许充电总压
 */
App_Tv100mvType UserStrategy_GetChargeVoltMax(void);
App_Tv100mvType UserStrategy_GetDC2ChargeVoltMax(void);

/**
 * \brief 获取充电机充电最大允许充电电流
 * \return 最大允许充电电流值
 */
Current_CurrentType UserStrategy_GetChargeCurrentMax(void);
Current_CurrentType UserStrategy_GetDC2ChargeCurrentMax(void);

/**
 * \brief 国标充电继电器是否准备就绪
 *
 * \param relayType 充电继电器类型
 * \return TRUE-就绪 FALSE-未就绪
 */
boolean UserStartegy_GBChargeRelayIsReady(RelayM_FunctionType relayType);

/**
 * \brief 获取MCU端总压值
 */
App_Tv100mvType UserStrategy_GetMcuVoltage(void);

/**
 * 是否可以安全下电
 * @return 返回TRUE时, 表示该任务已经关闭, 可以下电.
 */
boolean UserStrategy_SaftyOff(RuntimeM_SignalType signal);

/**
 * \brief 高压互锁故障
 * \note 可包含维修开关、其他高压互锁状态
 * \return 0-正常 非0-故障
 */
uint16 UserStrategy_IsDiagHvilAbnormal(void);

/**
 * \brief 安全气囊信号检测回调
 */
void UserStrategy_CheckSRS(const PwmCapture_DataType *dat);

/**
 * \brief 获取碰撞故障状态
 */
uint16 UserStrategy_GetCrashFault(void);

/**
 * \brief 用户自定义交流充电连接接口函数
 * \note 建议由连接到未连接变化时增加适当延时，保证连接状态不会突变而导致异常
 *
 * \return E_OK:已连接 E_NOT_OK:未连接
 */
Std_ReturnType UserStrategy_ACConnected(void);

/**
 * \brief 用户自定义直流充电连接接口函数
 * \note 建议由连接到未连接变化时增加适当延时，保证连接状态不会突变而导致异常
 *
 * \return E_OK:已连接 E_NOT_OK:未连接
 */
Std_ReturnType UserStrategy_DCConnected(void);
Std_ReturnType UserStrategy_DC2Connected(void);

/**
 * \brief 满充及满充释放事件钩子函数
 * \details 由满充及满充释放事件触发回调
 */
void UserStrategy_FullChargeHook(void);
void UserStrategy_FullChargeReleaseHook(void);
boolean UserStrategy_RemoteBalanceConditionCheck(void);


#endif

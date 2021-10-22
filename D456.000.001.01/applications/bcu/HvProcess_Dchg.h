/**
 * \file HvProcess_Dchg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压放电流程控制头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */

/**
 * \addtogroup HvProcess 高压流程控制
 * \{
 */

#ifndef HV_PROCESS__DCHG_H_
#define HV_PROCESS__DCHG_H_

#include "HvProcess_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

/**
 * \brief 放电高压流程控制状态类型
 */
typedef enum{
    HVPROCESS_DCHG_START = 0, /**< 启动状态 */
    HVPROCESS_DCHG_PRECHARGE, /**< 预充状态 */
    HVPROCESS_DCHG_HV_ON, /**< 高压上电状态 */
    HVPROCESS_DCHG_RELAY_OFF_DELAY, /**< 继电器断开延时状态 */
    HVPROCESS_DCHG_RESTART_ALLOW, /**< 允许重新启动状态 */
    HVPROCESS_DCHG_STATE_MAX, /**< 放电高压流程控制状态最大值 */
}HvProcess_DchgStateType;


/**
 * \brief 放电高压流程控制内部数据类型
 */
typedef struct{
    HvProcess_DchgStateType State; /**< 放电高压流程状态 */
    uint32 RelayOffTick; /**< 继电器断开计时 */
    boolean RelayFaultCheckFlag; /**< 继电器故障检查标志 */
    uint32 ChgRlyOnTick; /**< 充电继电器闭合延时 */
}HvProcess_DchgInnerDataType;


extern const HvProcess_StateConfigType HvProcess_DchgStateConfig[HVPROCESS_DCHG_STATE_MAX];

/**
 * \brief 放电高压流程控制初始化
 */
void HvProcess_DchgInit(Async_LooperType *looper);

/**
 * \brief 获取放电高压流程控制状态
 * \return 放电流程状态
 */
HvProcess_DchgStateType HvProcess_GetDchgState(void);

/**
 * \brief 设置放电高压流程控制状态
 *
 * \param state 放电流程状态
 */
void HvProcess_SetDchgState(HvProcess_DchgStateType state);

/**
 * \brief 放电高压流程控制周期函数
 * \details 用于需要周期性更新的策略
 */
void HvProcess_DchgPoll(void);

/**
 * \brief 放电启动状态条件函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DchgStateStartCond(void);

/**
 * \brief 放电启动状态动作函数
 */
void HvProcess_DchgStateStartAction(void);

/**
 * \brief 放电高压上电状态条件1函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DchgChargeConnectionCond(void);

/**
 * \brief 放电高压上电状态动作1函数
 */
void HvProcess_DchgChargeConnectionAction(void);

/**
 * \brief 放电高压上电状态条件2函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DchgFaultCond(void);

/**
 * \brief 放电高压上电状态动作2函数
 */
void HvProcess_DchgFaultAction(void);

/**
 * \brief 继电器断开延时条件
 * \return TRUE-成立 FALSE-不成立
 */
boolean HvProcess_DchgRelayOffDelayCond(void);

/**
 * \brief 继电器断开动作
 */
void HvProcess_DchgRelayOffDelayAction(void);

boolean HvProcess_DchgStatePrechargeCond(void);

void HvProcess_DchgStatePrechargeAction(void);
boolean HvProcess_DchgRestartAllowedCond(void);


#endif

/**
 * \}
 */

/**
 * \file HvProcess_DC2Chg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压充电流程控制头文件.
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

#ifndef HV_PROCESS_DC2_CHG_H_
#define HV_PROCESS_DC2_CHG_H_

#include "HvProcess_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"

/**
 * \brief 充电DC2高压流程控制状态类型
 */
typedef enum{
    HVPROCESS_DC2CHG_START = 0, /**< 启动状态 */
    HVPROCESS_DC2CHG_HV_ON = 1, /**< 高压上电状态 */
    HVPROCESS_DC2CHG_RELAY_OFF_DELAY = 2, /**< 继电器断开延时状态 */
    HVPROCESS_DC2CHG_STATE_MAX = 3, /**< 充电DC2高压流程控制状态最大值 */
}HvProcess_DC2ChgStateType;

/**
 * \brief 充电DC2高压流程控制内部数据类型
 */
typedef struct{
    uint8 chgFinishFlag; /**< 充电完成标志 */
    HvProcess_DC2ChgStateType State; /**< 充电DC2高压流程状态 */
    uint32 RelayOffTick; /**< 继电器断开计时 */
}HvProcess_DC2ChgInnerDataType;


extern const HvProcess_StateConfigType HvProcess_DC2ChgStateConfig[HVPROCESS_DC2CHG_STATE_MAX];


/**
 * \brief 充电DC2高压流程控制初始化
 */
void HvProcess_DC2ChgInit(Async_LooperType *looper);


/**
 * \brief 获取充电DC2高压流程控制状态
 * \return 充电流程状态
 */
HvProcess_DC2ChgStateType HvProcess_GetDC2ChgState(void);

/**
 * \brief 设置充电DC2高压流程控制状态
 *
 * \param state 充电流程状态
 */
void HvProcess_SetDC2ChgState(HvProcess_DC2ChgStateType state);

/**
 * \brief 充电DC2高压流程控制周期函数
 * \details 用于需要周期性更新的策略
 */
void HvProcess_DC2ChgPoll(void);

/**
 * \brief 充电启动状态条件函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DC2ChgStateStartCond(void);

/**
 * \brief 充电启动状态动作函数
 */
void HvProcess_DC2ChgStateStartAction(void);

/**
 * \brief 充电是否完成条件
 * \return TRUE-完成 FALSE-未完成
 */
boolean HvProcess_DC2ChgIsFinishCond(void);

/**
 * \brief 充电完成动作
 */
void HvProcess_DC2ChgFinishAction(void);

/**
 * \brief 充电DC2高压上电状态条件1函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DC2ChgChargeConnectionCond(void);

/**
 * \brief 充电DC2高压上电状态动作1函数
 */
void HvProcess_DC2ChgChargeConnectionAction(void);

/**
 * \brief 充电DC2高压上电状态条件2函数
 * \return TRUE-正常 FALSE-故障
 */
boolean HvProcess_DC2ChgFaultCond(void);

/**
 * \brief 充电DC2高压上电状态动作2函数
 */
void HvProcess_DC2ChgFaultAction(void);

/**
 * \brief 继电器断开延时条件
 * \return TRUE-成立 FALSE-不成立
 */
boolean HvProcess_DC2ChgRelayOffDelayCond(void);

/**
 * \brief 继电器断开动作
 */
void HvProcess_DC2ChgRelayOffDelayAction(void);


#endif

/**
 * \}
 */

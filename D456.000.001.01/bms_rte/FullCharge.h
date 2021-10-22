/**
 * \file FullCharge.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 满充策略头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170414 |
 */
#ifndef FULL_CHARGE_H_
#define FULL_CHARGE_H_

#include "App_Types.h"
#include "Async_Looper.h"
#include "Async_Event.h"
#include "Charge_Types.h"

/**
 * \brief 最小有效充电电流值
 */
#define FULLCHARGE_CHARGE_VALID_CURRENT_MIN     CURRENT_S_100MA_FROM_A(1)

/**
 * \brief 满充状态类型
 */
typedef enum{
    FULLCHARGE_STATE_NOT_OK, /**< 未满充状态 */
    FULLCHARGE_STATE_OK, /**< 满充状态 */
}FullCharge_StateType;

/**
 * \brief 满充内部数据类型
 */
typedef struct{
    uint8 flag; /**< 满充标志 */
    uint32 tick; /**< 计时 */
    uint32 relTick; /**< 释放计时 */
    uint8 chargeConnectOff; /**< 充电连接断开标志 */
    FullCharge_StateType state; /**< 满充状态 */
    Charge_ChargeType fullChargeType; /**< 满充充电类型 */
    Async_EventType event; /**< 异步事件 */
}FullCharge_InnerDataType;

typedef void (*FullCharge_FullChargeEventHook)(void);

/**
 * \brief 满充配置类型
 */
typedef struct{
    uint8 currentDecreaseEndFlag; /**< 充电降流末端检查标志 */
    uint32 fullChargeDelay; /**< 满充延时 */
    uint32 fullChargeRelDelay; /**< 满充释放延时 */
    uint16 fullChargeVolt; /**< 满充单体电压 */
    FullCharge_FullChargeEventHook fullHook; /**< 满充钩子函数 */
    FullCharge_FullChargeEventHook fullRelHook; /**< 满充释放钩子函数 */
}FullCharge_ConfigInfoType;

extern const FullCharge_ConfigInfoType FullCharge_ConfigInfo;

/**
 * \brief 满充检测模块初始化
 *
 * \param looper 异步Looper
 */
void FullCharge_Init(Async_LooperType *looper);

/**
 * \brief 获取满充状态
 * \return 0-未满充 非0-满充
 */
uint16 FullCharge_GetStatus(void);


#endif
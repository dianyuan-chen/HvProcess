/**
 * \file SystemStateM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 系统状态管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161208 |
 */

/**
 * \addtogroup SystemStateM 系统工作状态管理
 * \{
 */

#ifndef SYSTEMSTATEM_H_
#define SYSTEMSTATEM_H_

#include "Std_Types.h"

#if 0

/**
 * \brief 系统状态类型定义
 */
typedef enum{
    SYSTEMSTATEM_POWER_ON, /**< 上电自检状态 */
    SYSTEMSTATEM_STANDBY, /**< 待机状态 */
    SYSTEMSTATEM_DISCHARGE, /**< 放电状态 */
    SYSTEMSTATEM_CHARGE, /**< 充电状态 */
    SYSTEMSTATEM_FAULT, /**< 故障状态 */
    SYSTEMSTATEM_DIAGNOSIS, /**< 诊断状态 */
    SYSTEMSTATEM_POWER_DOWN, /**< 下电状态 系统下高压后状态 */
}SystemStateM_StateType;


/**
 * \brief 系统状态管理初始化
 */
void SystemStateM_Init(void);

/**
 * \brief 系统状态管理反初始化
 */
void SystemStateM_Deinit(void);


/**
 * \brief 获取系统状态
 *
 * \return 当前系统状态
 */
SystemStateM_StateType SystemStateM_GetState(void);

#endif


#endif


/**
 * \}
 */
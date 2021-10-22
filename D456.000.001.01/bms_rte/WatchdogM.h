/**
 * \file WatchdogM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 看门狗管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161212 |
 */

/**
 * \addtogroup WatchdogM 看门狗管理
 * \{
 */


#ifndef WATCHDOGM_H_
#define WATCHDOGM_H_

#include "Std_Types.h"

typedef uint8 WatchdogM_IdType;

/**
 * \brief 看门狗管理模块初始化
 */
void WatchdogM_Init(void);

/**
 * \brief 看门狗管理使能
 */
void WatchdogM_Enable(void);

/**
 * \brief 看门狗管理禁能
 */
void WatchdogM_Disable(void);

/**
 * \brief 看门狗监控任务注册
 *
 * \param Timeout 管理超时时间
 *
 * \return 监控任务ID 0xFF为无效ID
 */
WatchdogM_IdType WatchdogM_Register(uint16 ms);

/**
 * \brief 看门狗监控任务注销
 *
 * \param Id 监控任务ID
 *
 * \return E_OK:注销成功 E_NOT_OK:注销失败
 */
Std_ReturnType WatchdogM_Unregister(WatchdogM_IdType Id);

/**
 * \brief 看门狗监控任务喂狗
 * \note 通过对单个ID在超时时间内喂狗，以防止监控超时产生复位
 *
 * \param Id 监控任务ID
 */
void WatchdogM_Feed(WatchdogM_IdType Id);

/**
 * \brief 看门狗监控运行
 * \note 实时监控各注册过的任务的超时
 */
void WatchdogM_Run(void);

#endif

/**
 * \}
 */

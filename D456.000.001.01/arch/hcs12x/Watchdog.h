/**
 * \file Watchdog.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 看门狗头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161212 |
 */

/**
 * \addtogroup Watchdog 看门狗
 * \{
 */


#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "Std_Types.h"

/**
 * \brief 看门狗超时时间类型定义
 * \note 代表着看门狗的超时的晶振周期，单位为2幂次方
 */
typedef enum {
    WATCHDOG_DISABLE, /**< 看门狗关闭 */
    CR_POWER_14, /**< 2^14个晶振周期 */
    CR_POWER_16, /**< 2^16个晶振周期 */
    CR_POWER_18, /**< 2^18个晶振周期 */
    CR_POWER_20, /**< 2^20个晶振周期 */
    CR_POWER_22, /**< 2^22个晶振周期 */
    CR_POWER_23, /**< 2^23个晶振周期 */
    CR_POWER_24, /**< 2^24个晶振周期 */
} Watchdog_TimeoutType;

/**
 * \brief 看门狗配置参数类型定义
 */
typedef struct {
    Watchdog_TimeoutType timeout; /**< 看门狗超时时间 */
} Watchdog_ConfigType;

/**
 * \brief 看门狗模块初始化
 * \note 配置看门狗的超时时间等
 *
 * \param ConfigInfoPtr 配置参数指针
 */
void Watchdog_Init(const Watchdog_ConfigType *ConfigInfoPtr);

/**
 * \brief 看门狗喂狗操作
 */
void Watchdog_Feed(void);

void WatchDog_Reset(void);

#endif

/**
 * \}
 */
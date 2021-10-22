/**
 * \addtogroup Statistic
 * \{
 */

/**
 * \file Statistic_Cfg.h
 * \brief 统计配置文件
 */
#ifndef STATISTIC_CFG_H_
#define STATISTIC_CFG_H_

#include "App_Types.h"

/**
 * \brief 最高最低单体电压统计个数定义
 *
 * \remarks 程序设计仅支持1~4个
 */
#define STATISTIC_VOLTAGE_NUM	4U

/**
 * \brief 最高最低温度统计个数定义
 *
 * \remarks 程序设计仅支持1~4个
 */
#define STATISTIC_TEMPERATURE_NUM	4U

/**
 * \brief 电池充放电次数统计SOC阈值
 */
#define STATISTIC_DISCHARGE_CNT_LOW_SOC     PERCENT_TO_SOC(40U)
#define STATISTIC_DISCHARGE_CNT_HIGH_SOC    PERCENT_TO_SOC(90U)


#if STATISTIC_VOLTAGE_NUM == 0U || STATISTIC_VOLTAGE_NUM > 4U
	#error The define of "STATISTIC_VOLTAGE_NUM" should be a value in range from 1 to 4!
#endif
#if STATISTIC_TEMPERATURE_NUM == 0U || STATISTIC_TEMPERATURE_NUM > 4U
	#error The define of "STATISTIC_TEMPERATURE_NUM" should be a value in range from 1 to 4!
#endif

#endif

/** \} */
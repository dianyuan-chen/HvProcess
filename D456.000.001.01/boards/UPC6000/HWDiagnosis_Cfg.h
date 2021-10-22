/**
 * \file HWDiagnosis_PBCfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 硬件自检配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20161210 |
 */

/**
 * \addtogroup HWDiagnosis 硬件自检
 * \{
 */


#ifndef HWDIAGNOSIS_PBCFG_H_
#define HWDIAGNOSIS_PBCFG_H_

#include "Std_Types.h"

#define HWDIAGNOSIS_DEV_ERROR_DETECT            STD_OFF

/**
 * \brief 主机板载电压个数
 */
#define HWDIAGNOSIS_BCU_VOLT_MAX                9U

/**
 * \brief 单个从机板载电压个数定义
 */
#define HWDIAGNOSIS_SINGLE_BMU_VOLT_NUM         2U

/**
 * \brief 主机板载电压类型定义
 */
#define HWDIAGNOSIS_BCU_VOLT_24V                0U
#define HWDIAGNOSIS_BCU_VOLT_NAND_3V3           1U
#define HWDIAGNOSIS_BCU_VOLT_MCU_5V             2U
#define HWDIAGNOSIS_BCU_VOLT_PERIPHERAL_5V      3U
#define HWDIAGNOSIS_BCU_VOLT_RTC_3V3            4U
#define HWDIAGNOSIS_BCU_VOLT_INSU_N5V           5U
#define HWDIAGNOSIS_BCU_VOLT_HALL_8V            6U
#define HWDIAGNOSIS_BCU_VOLT_HALL_5V            7U
#define HWDIAGNOSIS_BCU_VOLT_ADS10XX            8U
/**
 * \brief 从机板载电压
 */
#define HWDIAGNOSIS_BMU_VOLT_0(bmu)             (HWDIAGNOSIS_BCU_VOLT_MAX + ((bmu) * HWDIAGNOSIS_SINGLE_BMU_VOLT_NUM))
#define HWDIAGNOSIS_BMU_VOLT_1(bmu)             (HWDIAGNOSIS_BCU_VOLT_MAX + 1U + ((bmu) * HWDIAGNOSIS_SINGLE_BMU_VOLT_NUM))

/**
 * \brief 板载电压最大个数定义
 */
#define HWDIAGNOSIS_VOLT_NUM_MAX                (HWDIAGNOSIS_BCU_VOLT_MAX + BCU_SLAVE_NUM_MAX * HWDIAGNOSIS_SINGLE_BMU_VOLT_NUM)






/**
 * \brief 主机板载温度个数
 */
#define HWDIAGNOSIS_BCU_TEMP_MAX                6U

/**
 * \brief 单个从机板载温度个数定义
 */
#define HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM         1U

/**
 * \brief 主机板载温度类型定义
 */
#define HWDIAGNOSIS_BCU_TEMP_NTC                0U
#define HWDIAGNOSIS_BCU_TEMP_RTC                1U
#define HWDIAGNOSIS_BCU_TEMP_ADS10XX1           2U
#define HWDIAGNOSIS_BCU_TEMP_ADS10XX2           3U
#define HWDIAGNOSIS_BCU_TEMP_MCU                4U
#define HWDIAGNOSIS_BCU_TEMP_SHUNT              5U
/**
 * \brief 从机板载温度
 */
#if HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM > 1U
#define HWDIAGNOSIS_BMU_TEMP_NTC(bmu)           (HWDIAGNOSIS_BCU_TEMP_MAX + ((bmu) * HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM))
#else
#define HWDIAGNOSIS_BMU_TEMP_NTC(bmu)           (HWDIAGNOSIS_BCU_TEMP_MAX + (bmu))
#endif

/**
 * \brief 板载温度最大个数定义
 */
#if HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM > 1U
#define HWDIAGNOSIS_TEMP_NUM_MAX                (HWDIAGNOSIS_BCU_TEMP_MAX + BCU_SLAVE_NUM_MAX * HWDIAGNOSIS_SINGLE_BMU_TEMP_NUM)
#else
#define HWDIAGNOSIS_TEMP_NUM_MAX                (HWDIAGNOSIS_BCU_TEMP_MAX + BCU_SLAVE_NUM_MAX)
#endif


#endif


/**
 * \}
 */

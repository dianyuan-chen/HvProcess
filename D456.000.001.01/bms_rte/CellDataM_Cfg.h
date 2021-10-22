/**
 * \file CellDataM_Cfg.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 电池数据管理配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20161227 |
 */

/**
 * \addtogroup CellDataM 电池数据管理
 * \{
 */


#ifndef CELLDATAM_CFG_H_
#define CELLDATAM_CFG_H_

#include "App_Types.h"

/**
 * \brief 单体电压最大值
 */
#define CELLDATAM_CELL_VOLTAGE_MAX      MV_FROM_V(65)

#define CELLDATAM_CELL_NORMAL_VOLTAGE_MIN   1500
#define CELLDATAM_CELL_NORMAL_VOLTAGE_MAX   4500

#endif


/**
 * \}
 */


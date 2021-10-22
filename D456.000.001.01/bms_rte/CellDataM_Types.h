/**
 * \file CellDataM_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 电池数据管理数据类型头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170116 |
 */

/**
 * \addtogroup CellDataM 电池数据管理
 * \{
 */

#ifndef CELLDATAM_TYPES_H_
#define CELLDATAM_TYPES_H_

#include "Std_Types.h"


/**
 * \brief 电池逻辑编号类型定义
 */
typedef uint16 CellDataM_CellLogicIndexType;

/**
 * \brief 电池物理编号类型定义
 */
typedef uint16 CellDataM_CellPhysicalIndexType;

/**
 * \brief 温度类型类型定义
 */
typedef enum{
    CELLDATAM_TEMPERATURE_TYPE_CELL, /**< 电池温度 */
    CELLDATAM_TEMPERATURE_TYPE_POLE, /**< 极柱温度 */
    CELLDATAM_TEMPERATURE_TYPE_HEAT, /**< 加热温度 */
    CELLDATAM_TEMPERATURE_TYPE_NUM
}CellDataM_TemperatureTypeType;


#endif

/**
 * \}
 */
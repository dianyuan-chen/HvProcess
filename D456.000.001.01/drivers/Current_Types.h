/**
 * \addtogroup CURRENT 电流采集
 * \{
 */

#ifndef CURRENT_TYPES_H
#define CURRENT_TYPES_H

#include "Std_Types.h"

/**
 * \brief 电流无效值定义
 */
#define CURRENT_INVALID_VALUE           (-32768)

/**
 * \brief 电流短路值定义
 */
#define CURRENT_SHORT_CIRCUIT_VALUE     (-32767)

/**
 * \brief 电流开路值定义
 */
#define CURRENT_OPEN_CIRCUIT_VALUE      (-32766)

/**
 * \brief 电流是否有效
 */
#define CURRENT_IS_VALID(CURRENT)       ((sint16)(CURRENT) > CURRENT_OPEN_CIRCUIT_VALUE)
#define CURRENT_IS_POSI_CURRENT(CURRENT)    ((sint16)(CURRENT) > 0)
#define CURRENT_IS_NEGA_CURRENT(CURRENT)    (CURRENT_IS_VALID(CURRENT) && (sint16)(CURRENT) <= 0)

/**
 * \brief 电流值类型
 * \details 单位0.1A.
 * \note > 0: 充电
 * 		<= 0: 放电
 */
typedef sint16 Current_CurrentType;

/**
 * 带时间戳的电流.
 * \details 时间精度1ms, 单位0.1A.
 */
typedef struct {
    uint32 timestamp;
    Current_CurrentType current;
} Current_TimedCurrentType;

typedef struct {
    Current_CurrentType zeroFilter;
    Current_CurrentType zeroOffset;
} Current_SensorCalibrateParam;


#endif

/** \} */
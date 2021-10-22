/**
 * \addtogroup app_types 应用层类型
 * \{
 */

/**
 * \file App_Types.h
 * \brief 应用层类型定义文件
 */

#ifndef APP_DEFS_H_
#define APP_DEFS_H_

#include "Std_Types.h"
#include "Buffer.h"

/**
 * \brief 从机最大个数配置
 *
 * \remarks 此参数最大值不能超过16
 */
#define BCU_SLAVE_NUM_MAX                   (16U)

/**
 * \brief 单个从机支持的LTC6804个数
 */
#define BMU_LTC6804_NUM_MAX                 (5U)

/**
 * \brief 温度偏移量定义
 */
#define TEMPERATURE_OFFSET              50

/**
 * \brief 从机编号类型定义
 */
typedef uint8 App_SlaveIdType;

/**
 * \brief 容量类型定义
 */
typedef uint16 App_CapType;

/**
 * \brief SOC类型定义 精度0.1%
 */
typedef uint16 App_SocType;

/**
 * \brief SOH类型定义 精度0.1%
 */
typedef uint16 App_SohType;

/**
 * \brief 电流类型定义
 */
typedef uint16 App_CurrentType;

/**
 * \brief 电压类型定义
 */
typedef uint16 App_VoltageType;

/**
 * \brief 总压类型定义
 */
typedef uint16 App_Tv100mvType;

/**
 * \brief 高精度总压类型定义
 */
typedef uint32 App_Tv1mvType;

/**
 * \brief 温度类型定义
 */
typedef uint8 App_TemperatureType;


/**
 * \brief 电池类型定义
 */
typedef enum {
    APP_BATTERY_TYPE_UNKNOWN = 0x00, /**< 未知类型 */
    APP_BATTERY_TYPE_LEAD_ACID = 0x01, /**< 铅酸电池 */
    APP_BATTERY_TYPE_NIMH = 0x02, /**< 镍氢电池 */
    APP_BATTERY_TYPE_LIFEPO4 = 0x03, /**< 磷酸铁锂电池 */
    APP_BATTERY_TYPE_LIMN2O4 = 0x04, /**< 锰酸锂电池 */
    APP_BATTERY_TYPE_LICOO2 = 0x05, /**< 钴酸锂电池 */
    APP_BATTERY_TYPE_TERNARY = 0x06, /**< 三元材料电池 */
    APP_BATTERY_TYPE_POLYMER_LI_LON = 0x07, /**< 聚合物锂离子电池 */
    APP_BATTERY_TYPE_LI4O4TI = 0x08, /**< 钛酸锂电池 */
    APP_BATTERY_TYPE_OTHERS = 0xFF, /**< 其他类型电池 */
}App_BatteryTypeType;

/**
 * \brief SOC macro
 */
#define SOC_TO_UINT8(VALUE)             (DIVISION(VALUE, 4U))
#define SOC_TO_PERCENT(VALUE)           (DIVISION(VALUE, 10U))
#define PERCENT_TO_SOC(VALUE)           ((uint16)(VALUE) * 10U)

/**
 * \brief SOH macro
 */
#define SOH_TO_UINT8(VALUE)             (DIVISION(VALUE, 4U))
#define SOH_TO_PERCENT(VALUE)           (DIVISION(VALUE, 10U))
#define PERCENT_TO_SOH(VALUE)           ((uint16)(VALUE) * 10U)

/**
 * \brief Cap macro
 */
#define CAP_TO_AH(VALUE)                (DIVISION(VALUE, 10U))
#define CAP_FROM_AH(VALUE)              ((VALUE) * 10U)

#define AS_TO_AH(VALUE)                 ((uint16)DIVISION(VALUE, 3600U))
#define AS_TO_CAP(VALUE)                ((uint16)DIVISION(VALUE, 360U))
#define MAS_TO_AH(VALUE)                ((uint16)DIVISION(VALUE, 3600000U))
#define CAP_FROM_100UAS(VALUE)          MAS_TO_AH(VALUE)
#define AH_FROM_100UAS(VALUE)           ((uint16)DIVISION(VALUE, 36000000U))
#define CAP_10MAH_FROM_100UAS(VALUE)    ((uint16)DIVISION(VALUE, 360000U))
#define AS_FROM_100UAS(VALUE)           (DIVISION(VALUE, 10000UL))

#define AH_TO_AS(VALUE)                 ((uint32)(VALUE) * 3600UL)
#define CAP_TO_AS(VALUE)                ((uint32)(VALUE) * 360UL)
#define AH_TO_MAS(VALUE)                ((uint32)(VALUE) * 3600000UL)
#define CAP_TO_100UAS(VALUE)            AH_TO_MAS(VALUE)
#define AH_TO_100UAS(VALUE)             ((uint32)(VALUE) * 36000000UL)
#define AS_TO_100UAS(VALUE)             ((uint32)(VALUE) * 10000UL)

#define WH_TO_MWS(VALUE)                ((uint32)(VALUE) * 3600000UL)
#define WH_FROM_MWS(VALUE)              (DIVISION(VALUE, 3600000UL))

/**
 * \brief Current macro
 */
#define CURRENT_100MA_TO_A(VALUE)       (DIVISION(VALUE, 10U))
#define CURRENT_100MA_FROM_A(VALUE)     (10U * (VALUE))
#define CURRENT_S_100MA_TO_A(VALUE)     (DIVISION_S(VALUE, 10))
#define CURRENT_S_100MA_FROM_A(VALUE)   (10 * (VALUE))

/**
 * \brief Voltage marco
 */
#define MV_TO_V(VALUE)                  (DIVISION(VALUE, 1000U))
#define MV_FROM_V(VALUE)                ((VALUE) * 1000U)
#define MV_TO_100MV(VALUE)              (DIVISION(VALUE, 100U))
#define MV_FROM_100MV(VALUE)            ((VALUE) * 100U)
#define MV_TO_10MV(VALUE)               (DIVISION(VALUE, 10U))
#define MV_FROM_10MV(VALUE)             ((VALUE) * 10U)
#define V_TO_100MV(VALUE)               ((VALUE) * 10U)
#define V_FROM_100MV(VALUE)             (DIVISION(VALUE, 10U))

#define VOLT_4_DISPLAY(VALUE)           (CellDataM_VoltageIsValid(VALUE) ? (VALUE) : 0U)

/**
 * \brief Temperature macro
 */
#define TEMPERATURE_TO_C(VALUE)         ((uint8)(VALUE) - (uint8)(TEMPERATURE_OFFSET))
#define TEMPERATURE_FROM_C(VALUE)       (TEMPERATURE_OFFSET + (VALUE))

#define TEMP_TO_40_OFFSET(VALUE)        (CellDataM_TemperatureIsValid((uint16)(VALUE)) ? ((VALUE) >= 10U ? ((VALUE) - 10U) : 0U) : (VALUE))
#define TEMP_4_DISPLAY(VALUE)           (CellDataM_TemperatureIsValid((uint16)(VALUE)) ? (VALUE) : 0U)

#define TEMP_C_FROM_40_OFFSET(VALUE)    ((VALUE) - 40U)
#define TEMP_C_TO_40_OFFSET(VALUE)      ((VALUE) + 40U)

/**
 * \brief pwm duty
 */
#define PWM_DUTY_TO_PERCENT(VALUE)      (DIVISION((VALUE), 10U))
#define PWM_DUTY_FROM_PERCENT(VALUE)    ((VALUE) * 10U)

/**
 * \brief pwm frequence
 */
#define PWM_FREQ_TO_HZ(VALUE)           (VALUE)
#define PWM_FREQ_FROM_HZ(VALUE)         (VALUE)

/**
 * \brief 百分比转换
 */
#define PERCENT_TO_THOUSAND(VALUE)      ((VALUE) * 10U)
#define THOUSAND_TO_PERCENT(VALUE)      (DIVISION(VALUE, 10U))

/**
 * \brief 绝缘阻值
 */
#define INSU_TO_RES(VALUE)              ((VALUE) * 1000U)
#define INSU_FROM_RES(VALUE)            (DIVISION(VALUE, 1000U))

/**
 * \brief 时间转换
 */
#define S_TO_MS(VALUE)                  ((VALUE) * 1000U)
#define MS_TO_S(VALUE)                  ((VALUE) / 1000U)
#define S_TO_MIN(VALUE)                 ((VALUE) / 60U)
#define MIN_TO_S(VALUE)                 ((VALUE) * 60U)
#define HOUR_TO_MIN(VALUE)              ((VALUE) * 60U)
#define MIN_TO_HOUR(VALUE)              ((VALUE) / 60U)
#define HOUR_TO_S(VALUE)                ((VALUE) * 3600U)
#define S_TO_HOUR(VALUE)                ((VALUE) / 3600U)

#define MS_GET_INTERNAL(OLD, NEW)       ((NEW) - (OLD))

/**********************************************
 *
 * set or get data
 *
 ***********************************************/
#define GET_BT_UINT32   Buffer_GetBTUint32
#define GET_BT_UINT24   Buffer_GetBTUint24
#define GET_BT_UINT16   Buffer_GetBTUint16
#define GET_BT_UINT8    Buffer_GetBTUint8
#define GET_LT_UINT32   Buffer_GetLTUint32
#define GET_LT_UINT24   Buffer_GetLTUint24
#define GET_LT_UINT16   Buffer_GetLTUint16
#define GET_LT_UINT8    Buffer_GetLTUint8

#define SET_BT_UINT32   Buffer_SetBTUint32
#define SET_BT_UINT24   Buffer_SetBTUint24
#define SET_BT_UINT16   Buffer_SetBTUint16
#define SET_BT_UINT8    Buffer_SetBTUint8
#define SET_LT_UINT32   Buffer_SetLTUint32
#define SET_LT_UINT24   Buffer_SetLTUint24
#define SET_LT_UINT16   Buffer_SetLTUint16
#define SET_LT_UINT8    Buffer_SetLTUint8

/**********************************************
 *
 * read or write data and the position is moved
 *
 ***********************************************/
#define READ_BT_UINT32(buffer, pos)   Buffer_ReadBTUint32(buffer, &(pos))
#define READ_BT_UINT24(buffer, pos)   Buffer_ReadBTUint24(buffer, &(pos))
#define READ_BT_UINT16(buffer, pos)   Buffer_ReadBTUint16(buffer, &(pos))
#define READ_BT_UINT8(buffer, pos)    Buffer_ReadBTUint8(buffer, &(pos))
#define READ_LT_UINT32(buffer, pos)   Buffer_ReadLTUint32(buffer, &(pos))
#define READ_LT_UINT24(buffer, pos)   Buffer_ReadLTUint24(buffer, &(pos))
#define READ_LT_UINT16(buffer, pos)   Buffer_ReadLTUint16(buffer, &(pos))
#define READ_LT_UINT8(buffer, pos)    Buffer_ReadLTUint8(buffer, &(pos))


#define READ_BT_UINT32_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadBTUint32WithSize(buffer, &(pos), (uint16)(size))
#define READ_BT_UINT24_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadBTUint24WithSize(buffer, &(pos), (uint16)(size))
#define READ_BT_UINT16_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadBTUint16WithSize(buffer, &(pos), (uint16)(size))
#define READ_BT_UINT8_WITH_DATA_SIZE(buffer, pos, size)     Buffer_ReadBTUint8WithSize(buffer, &(pos), (uint16)(size))
#define READ_LT_UINT32_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadLTUint32WithSize(buffer, &(pos), (uint16)(size))
#define READ_LT_UINT24_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadLTUint24WithSize(buffer, &(pos), (uint16)(size))
#define READ_LT_UINT16_WITH_DATA_SIZE(buffer, pos, size)    Buffer_ReadLTUint16WithSize(buffer, &(pos), (uint16)(size))
#define READ_LT_UINT8_WITH_DATA_SIZE(buffer, pos, size)     Buffer_ReadLTUint8WithSize(buffer, &(pos), (uint16)(size))

#define WRITE_BT_UINT32(buffer, pos, value)     Buffer_WriteBTUint32(buffer, &(pos), (uint32)(value))
#define WRITE_BT_UINT24(buffer, pos, value)     Buffer_WriteBTUint24(buffer, &(pos), (uint32)(value))
#define WRITE_BT_UINT16(buffer, pos, value)     Buffer_WriteBTUint16(buffer, &(pos), (uint16)(value))
#define WRITE_BT_UINT8(buffer, pos, value)      Buffer_WriteBTUint8(buffer, &(pos), (uint8)(value))
#define WRITE_LT_UINT32(buffer, pos, value)     Buffer_WriteLTUint32(buffer, &(pos), (uint32)(value))
#define WRITE_LT_UINT24(buffer, pos, value)     Buffer_WriteLTUint24(buffer, &(pos), (uint32)(value))
#define WRITE_LT_UINT16(buffer, pos, value)     Buffer_WriteLTUint16(buffer, &(pos), (uint16)(value))
#define WRITE_LT_UINT8(buffer, pos, value)      Buffer_WriteLTUint8(buffer, &(pos), (uint8)(value))

#define WRITE_BT_UINT32_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteBTUint32WithSize(buffer, &(pos), (uint32)(value), (uint16)(size))
#define WRITE_BT_UINT24_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteBTUint24WithSize(buffer, &(pos), (uint32)(value), (uint16)(size))
#define WRITE_BT_UINT16_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteBTUint16WithSize(buffer, &(pos), (uint16)(value), (uint16)(size))
#define WRITE_BT_UINT8_WITH_BUFF_SIZE(buffer, pos, value, size)     Buffer_WriteBTUint8WithSize(buffer, &(pos), (uint8)(value), (uint16)(size))
#define WRITE_LT_UINT32_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteLTUint32WithSize(buffer, &(pos), (uint32)(value), (uint16)(size))
#define WRITE_LT_UINT24_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteLTUint24WithSize(buffer, &(pos), (uint32)(value), (uint16)(size))
#define WRITE_LT_UINT16_WITH_BUFF_SIZE(buffer, pos, value, size)    Buffer_WriteLTUint16WithSize(buffer, &(pos), (uint16)(value), (uint16)(size))
#define WRITE_LT_UINT8_WITH_BUFF_SIZE(buffer, pos, value, size)     Buffer_WriteLTUint8WithSize(buffer, &(pos), (uint8)(value), (uint16)(size))

#endif

/** \} */

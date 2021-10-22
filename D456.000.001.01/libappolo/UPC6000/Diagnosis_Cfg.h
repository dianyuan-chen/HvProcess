/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Generate by template render, DONOT edit it
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

/**
 * \addtogroup Diagnosis
 */

#ifndef DIAGNOSIS_CFG_H_
#define DIAGNOSIS_CFG_H_

#include "ChgSckTmpM_Cfg.h"

#define DIAGNOSIS_DEV_ERROR_DETECT          STD_OFF

#define DIAGNOSIS_SUPPORT_LEVEL             4U /**< 支持的报警等级 */

#define DIAGNOSIS_CALIB_ITEM_NUM            (((uint8)DIAGNOSIS_ITEM_CALIBRATE_STOP-(uint8)DIAGNOSIS_ITEM_CALIBRATE_START)+1U)
#define DIAGNOSIS_ITEM_DEFAULT_NUM          ((((uint8)DIAGNOSIS_ITEM_CALIBRATE_STOP-(uint8)DIAGNOSIS_ITEM_CALIBRATE_START)+1U) + \
                                            ((uint8)DIAGNOSIS_ITEM_NONE_CALIBRATE_STOP-(uint8)DIAGNOSIS_ITEM_NONE_CALIBRATE_START)+1U)

#define DIAGNOSIS_IS_CALIB_ITEM(item)       ((item) >= DIAGNOSIS_ITEM_CALIBRATE_START && (item) <= DIAGNOSIS_ITEM_CALIBRATE_STOP)
#define DIAGNOSIS_IS_NONE_CALIB_ITEM(item)  ((item) >= DIAGNOSIS_ITEM_NONE_CALIBRATE_START && (item) <= DIAGNOSIS_ITEM_NONE_CALIBRATE_STOP)


/**
 * \brief 诊断条目.
 */
typedef enum {
    DIAGNOSIS_ITEM_CHG_HV = 0, /**< 充电单体电压高 */
    DIAGNOSIS_ITEM_CALIBRATE_START = 0,
    DIAGNOSIS_ITEM_VOLT_START = 0,
    DIAGNOSIS_ITEM_DCHG_HV = 1, /**< 放电单体电压高 */
    DIAGNOSIS_ITEM_CHG_LV = 2, /**< 充电单体电压低 */
    DIAGNOSIS_ITEM_DCHG_LV = 3, /**< 放电单体电压低 */
    DIAGNOSIS_ITEM_CHG_HTV = 4, /**< 充电总压高 */
    DIAGNOSIS_ITEM_DCHG_HTV = 5, /**< 放电总压高 */
    DIAGNOSIS_ITEM_CHG_LTV = 6, /**< 充电总压低 */
    DIAGNOSIS_ITEM_DCHG_LTV = 7, /**< 放电总压低 */
    DIAGNOSIS_ITEM_CHG_DTV = 8, /**< 充电总压压差 */
    DIAGNOSIS_ITEM_DCHG_DTV = 9, /**< 放电总压压差 */
    DIAGNOSIS_ITEM_CHG_DV = 10, /**< 充电单体压差 */
    DIAGNOSIS_ITEM_DCHG_DV = 11, /**< 放电单体压差 */
    DIAGNOSIS_ITEM_VOLT_STOP = 11,
    DIAGNOSIS_ITEM_CHG_HT = 12, /**< 充电高温 */
    DIAGNOSIS_ITEM_TEMPERATURE_START = 12,
    DIAGNOSIS_ITEM_DCHG_HT = 13, /**< 放电高温 */
    DIAGNOSIS_ITEM_CHG_LT = 14, /**< 充电低温 */
    DIAGNOSIS_ITEM_DCHG_LT = 15, /**< 放电低温 */
    DIAGNOSIS_ITEM_CHG_DT = 16, /**< 充电温差 */
    DIAGNOSIS_ITEM_DCHG_DT = 17, /**< 放电温差 */
    DIAGNOSIS_ITEM_TEMPERATURE_STOP = 17,
    DIAGNOSIS_ITEM_DC_CHG_OC = 18, /**< 快充过流 */
    DIAGNOSIS_ITEM_CURRENT_START = 18,
    DIAGNOSIS_ITEM_AC_CHG_OC = 19, /**< 慢充过流 */
    DIAGNOSIS_ITEM_FB_OC = 20, /**< 回馈过流 */
    DIAGNOSIS_ITEM_DCHG_OC = 21, /**< 持续放电过流 */
    DIAGNOSIS_ITEM_SP_OC = 22, /**< 瞬时放电过流 */
    DIAGNOSIS_ITEM_CURRENT_STOP = 22,
    DIAGNOSIS_ITEM_HSOC = 23, /**< SOC过高 */
    DIAGNOSIS_ITEM_SOC_START = 23,
    DIAGNOSIS_ITEM_LSOC = 24, /**< SOC过低 */
    DIAGNOSIS_ITEM_SOC_STOP = 24,
    DIAGNOSIS_ITEM_LEAK = 25, /**< 绝缘漏电 */
    DIAGNOSIS_ITEM_CHG_HEAT_HT = 26, /**< 充电加热高温 */
    DIAGNOSIS_ITEM_DCHG_HEAT_HT = 27, /**< 放电加热高温 */
    DIAGNOSIS_ITEM_CHG_HEAT_DT = 28, /**< 充电加热温差 */
    DIAGNOSIS_ITEM_DCHG_HEAT_DT = 29, /**< 放电加热温差 */
    DIAGNOSIS_ITEM_CHG_HEAT_TIMEOUT = 30, /**< 充电加热超时 */
    DIAGNOSIS_ITEM_DCHG_HEAT_TIMEOUT = 31, /**< 放电加热超时 */
    DIAGNOSIS_ITEM_CHG_HEAT_OC = 32, /**< 充电加热过流 */
    DIAGNOSIS_ITEM_DCHG_HEAT_OC = 33, /**< 放电加热过流 */
    DIAGNOSIS_ITEM_SOC_JUMP = 34, /**< SOC跳变 */
    DIAGNOSIS_ITEM_SUPPLY_VOL_LOW = 35, /**< 供电电压过低 */
    DIAGNOSIS_ITEM_CHG_POLE_HT = 36, /**< 充电极柱高温 */
    DIAGNOSIS_ITEM_DCHG_POLE_HT = 37, /**< 放电极柱高温 */
    DIAGNOSIS_ITEM_CHG_POLE_DT = 38, /**< 充电极柱温差 */
    DIAGNOSIS_ITEM_DCHG_POLE_DT = 39, /**< 放电极柱温差 */
    DIAGNOSIS_ITEM_CHG_CUR_FAULT = 40, /**< 充电电流异常 */
    DIAGNOSIS_ITEM_SUPPLY_VOL_HIGH = 41, /**< 供电电压过高 */
    DIAGNOSIS_ITEM_CALIBRATE_STOP = 41,
    DIAGNOSIS_ITEM_VOLT_LINE = 128, /**< 电压排线脱落 */
    DIAGNOSIS_ITEM_NONE_CALIBRATE_START = 128,
    DIAGNOSIS_ITEM_LINE_START = 128,
    DIAGNOSIS_ITEM_TEMP_LINE = 129, /**< 温感排线脱落 */
    DIAGNOSIS_ITEM_LINE_STOP = 129,
    DIAGNOSIS_ITEM_INTER_COMM = 130, /**< 内网通信 */
    DIAGNOSIS_ITEM_CHGSCKTMP_DC_POSITIVE = 131, /**< 快充正极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_START = 131,
    DIAGNOSIS_ITEM_CHGSCKTMP_DC_NEGATIVE = 132, /**< 快充负极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_AL = 133, /**< 慢充AL极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_BN = 134, /**< 慢充BN极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_AC_C = 135, /**< 慢充C极高温 */
    DIAGNOSIS_ITEM_CHGSCKTMP_STOP = 135,
    DIAGNOSIS_ITEM_CHARGER_COMM = 136, /**< 充电机通信 */
    DIAGNOSIS_ITEM_VCU_COMM = 137, /**< 整车通信 */
    DIAGNOSIS_ITEM_FULL_CHARGE = 138, /**< 满充 */
    DIAGNOSIS_ITEM_CHGSCKTMP_ABNORMAL = 139, /**< 充电插座温感异常 */
    DIAGNOSIS_ITEM_PRECHARGE_FAILURE = 140, /**< 预充失败 */
    DIAGNOSIS_ITEM_CURRENT_ABNORMAL = 141, /**< 电流异常 */
    DIAGNOSIS_ITEM_BMS_INIT_FAILURE = 142, /**< BMS初始化故障 */
    DIAGNOSIS_ITEM_HVIL_ABNORMAL = 143, /**< HVIL故障 */
    DIAGNOSIS_ITEM_RELAY_ABNORMAL = 144, /**< 继电器故障 */
    DIAGNOSIS_ITEM_HEAT_FAULT = 145, /**< 加热故障 */
    DIAGNOSIS_ITEM_CC2_CONNECT_FAULT = 146, /**< CC2连接故障 */
    DIAGNOSIS_ITEM_CC_CONNECT_FAULT = 147, /**< CC连接故障 */
    DIAGNOSIS_ITEM_CP_CONNECT_FAULT = 148, /**< CP连接故障 */
    DIAGNOSIS_ITEM_HEAT_TEMP_LINE_FAULT = 149, /**< 加热温感异常 */
    DIAGNOSIS_ITEM_POLE_TEMP_LINE_FAULT = 150, /**< 极柱温感异常 */
    DIAGNOSIS_ITEM_EL_FAULT = 151, /**< 电子锁故障 */
    DIAGNOSIS_ITEM_DOUBLE_CHG_CONNECT_FAULT = 152, /**< 多充电连接故障 */
    DIAGNOSIS_ITEM_ACT_BAT_NUM = 153, /**< 电池数不匹配 */
    DIAGNOSIS_ITEM_ACT_TMP_NUM = 154, /**< 温感数不匹配 */
    DIAGNOSIS_ITEM_SUPPLY_VOL_ABNOMAL = 155, /**< 供电电压异常 */
    DIAGNOSIS_ITEM_CRASH_FAULT = 156, /**< 碰撞故障 */
    DIAGNOSIS_ITEM_NONE_CALIBRATE_STOP = 156,

    DIAGNOSIS_ITEM_MAX_NUM = 157,

    DIAGNOSIS_ITEM_INVALID_INDEX = 0xFF /**< 无效编号 */
} Diagnosis_ItemType;


#endif

/** \} */

/**
 * \file Charge_Types.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电类型头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170216 |
 */

#ifndef CHARGE_TYPES_H_
#define CHARGE_TYPES_H_

#include "App_Types.h"

/**
 * \brief 充电类型定义
 */
#define CHARGE_TYPE_NONE     0U
#define CHARGE_TYPE_DC       1U
#define CHARGE_TYPE_AC       2U

#define CHARGE_TYPE_INVALID  0xFFU

/**
 * \brief 充电类型定义
 */
typedef uint8 Charge_ChargeType;


typedef struct{
    App_Tv100mvType chargeTotalVoltMax; /**< 最高允许充电总压 0.1V */
    App_CurrentType chargeCurrentMax; /**< 最大允许充电电流 0.1A */
    App_CurrentType chargeCurrentMin; /**< 最小允许充电电流(截止充电电流) 0.1A */
    App_Tv100mvType fullChargeRelTotalVolt; /**< 满充释放总压 0.1V */
}Charge_CalibConfigParaType;

/**
 * \brief 充电管理标定配置参数类型定义
 */
typedef struct{
    Charge_CalibConfigParaType AC_Para; /**< 交流充电标定参数 */
    Charge_CalibConfigParaType DC_Para; /**< 直流充电标定参数 */
}Charge_CalibConfigInfoType;


#endif
/**
 * \file FullCharge_Lcfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 满充策略链接配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170524 |
 */

#include "FullCharge.h"
#include "UserStrategy.h"
#include "CellDataM.h"

const FullCharge_ConfigInfoType FullCharge_ConfigInfo = {
    TRUE, /**< currentDecreaseEndFlag: 充电降流末端检查标志 */
    5000UL, /**< fullChargeDelay: 满充延时 */
    5000UL, /**< fullChargeRelDelay: 满充释放延时 */
    CELL_VOLTAGE_INVALID_VALUE, /**< fullChargeVolt: 满充单体电压 */
    UserStrategy_FullChargeHook, /**< fullHook: 满充钩子函数 */
    UserStrategy_FullChargeReleaseHook, /**< fullRelHook: 满充释放钩子函数 */
};

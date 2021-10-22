/**
 * \file ChargeM_LCfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 充电管理配置头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170306 |
 */
#include "ChargeM.h"

const ChargeM_ConfigInfoType ChargeM_ConfigInfo = {
    // AC
    {
        STD_ON, /**< AC_Enable：交流充电使能控制 */
        20U, /**< chargeTimeMax: 最大允许充电时间 */
    },
    // DC
    {
        STD_ON, /**< DC_Enable：直流充电使能控制 */
        15U, /**< chargeTimeMax: 最大允许充电时间 */
    },
};

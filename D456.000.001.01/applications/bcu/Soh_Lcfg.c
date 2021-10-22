/**
 * \file Soh_Lcfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief SOH配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20190517 |
 */
#include "Soh.h"

const Soh_ConfigInfoType Soh_ConfigInfo = {
    TRUE, /**< isMonitorNominalCapChange: soh是否监控程序额定容量变化 */
};

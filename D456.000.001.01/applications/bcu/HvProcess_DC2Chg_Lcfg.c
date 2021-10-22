/**
 * \file HvProcess_DC2Chg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压充电流程控制配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */
#include "HvProcess_Types.h"
#include "HvProcess_DC2Chg.h"

const HvProcess_StateInfoType HvProcess_DC2ChgStartInfoConfig[] = {
    {
        HvProcess_DC2ChgStateStartCond, /**< Cond: 条件函数指针 */
        HvProcess_DC2ChgStateStartAction, /**< Action: 动作函数指针 */
        (uint16)HVPROCESS_DC2CHG_HV_ON, /**< Next: 下一状态 */
    },
};

const HvProcess_StateInfoType HvProcess_DC2ChgHvOnInfoConfig[] = {
    {
        HvProcess_DC2ChgChargeConnectionCond, /**< Cond: 条件函数指针 */
        HvProcess_DC2ChgChargeConnectionAction, /**< Action: 动作函数指针 */
        (uint16)HVPROCESS_DC2CHG_RELAY_OFF_DELAY, /**< Next: 下一状态 */
    },
    {
        HvProcess_DC2ChgFaultCond, /**< Cond: 条件函数指针 */
        HvProcess_DC2ChgFaultAction, /**< Action: 动作函数指针 */
        (uint16)HVPROCESS_DC2CHG_RELAY_OFF_DELAY, /**< Next: 下一状态 */
    },
};

const HvProcess_StateInfoType HvProcess_DC2ChgRelayOffDelayInfoConfig[] = {
    {
        HvProcess_DC2ChgRelayOffDelayCond, /**< Cond: 条件函数指针 */
        HvProcess_DC2ChgRelayOffDelayAction, /**< Action: 动作函数指针 */
        (uint16)HVPROCESS_DC2CHG_START, /**< Next: 下一状态 */
    },
};

const HvProcess_StateConfigType HvProcess_DC2ChgStateConfig[HVPROCESS_DC2CHG_STATE_MAX] = {
    {
        (uint8)ARRAY_SIZE(HvProcess_DC2ChgStartInfoConfig), /**< Num: 状态配置个数 */
        HvProcess_DC2ChgStartInfoConfig, /**< State: 状态信息指针 */
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DC2ChgHvOnInfoConfig), /**< Num: 状态配置个数 */
        HvProcess_DC2ChgHvOnInfoConfig, /**< State: 状态信息指针 */
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DC2ChgRelayOffDelayInfoConfig), /**< Num: 状态配置个数 */
        HvProcess_DC2ChgRelayOffDelayInfoConfig, /**< State: 状态信息指针 */
    },
};

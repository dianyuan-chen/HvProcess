/**
 * \file HvProcess_Dchg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压放电流程控制配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */

#include "HvProcess_Dchg.h"

const HvProcess_StateInfoType HvProcess_DchgStartInfoConfig[] = {
    {
        HvProcess_DchgStateStartCond,
        HvProcess_DchgStateStartAction,
        (uint16)HVPROCESS_DCHG_PRECHARGE,
    }
};

const HvProcess_StateInfoType HvProcess_DchgPrechargeInfoConfig[] = {
    {
        HvProcess_DchgChargeConnectionCond,
        HvProcess_DchgChargeConnectionAction,
        (uint16)HVPROCESS_DCHG_RELAY_OFF_DELAY,
    },
    {
        HvProcess_DchgFaultCond,
        HvProcess_DchgFaultAction,
        (uint16)HVPROCESS_DCHG_RELAY_OFF_DELAY,
    },
    {
        HvProcess_DchgStatePrechargeCond,
        HvProcess_DchgStatePrechargeAction,
        (uint16)HVPROCESS_DCHG_HV_ON,
    }
};

const HvProcess_StateInfoType HvProcess_DchgHvOnInfoConfig[] = {
    {
        HvProcess_DchgChargeConnectionCond,
        HvProcess_DchgChargeConnectionAction,
        (uint16)HVPROCESS_DCHG_RELAY_OFF_DELAY,
    },
    {
        HvProcess_DchgFaultCond,
        HvProcess_DchgFaultAction,
        (uint16)HVPROCESS_DCHG_RELAY_OFF_DELAY,
    },
};

const HvProcess_StateInfoType HvProcess_DchgRelayOffDelayInfoConfig[] = {
    {
        HvProcess_DchgRelayOffDelayCond,
        HvProcess_DchgRelayOffDelayAction,
        (uint16)HVPROCESS_DCHG_RESTART_ALLOW,
    }
};

const HvProcess_StateInfoType HvProcess_DchgRestartInfoConfig[] = {
    {
        HvProcess_DchgRestartAllowedCond,
        NULL,
        (uint16)HVPROCESS_DCHG_START,
    }
};

const HvProcess_StateConfigType HvProcess_DchgStateConfig[HVPROCESS_DCHG_STATE_MAX] = {
    {
        (uint8)ARRAY_SIZE(HvProcess_DchgStartInfoConfig),
        HvProcess_DchgStartInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DchgPrechargeInfoConfig),
        HvProcess_DchgPrechargeInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DchgHvOnInfoConfig),
        HvProcess_DchgHvOnInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DchgRelayOffDelayInfoConfig),
        HvProcess_DchgRelayOffDelayInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_DchgRestartInfoConfig),
        HvProcess_DchgRestartInfoConfig,
    },
};


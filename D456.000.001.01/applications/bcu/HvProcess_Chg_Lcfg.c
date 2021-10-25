/**
 * \file HvProcess_Chg.c
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
#include "HvProcess_Chg.h"

const HvProcess_StateInfoType HvProcess_ChgStartInfoConfig[] = {
    {
        HvProcess_ChgStateStartCond,
        HvProcess_ChgStateStartAction,
        (uint16)HVPROCESS_CHG_HV_ON,
    }
};

const HvProcess_StateInfoType HvProcess_ChgHvOnInfoConfig[] = {
    {
        HvProcess_ChgChargeConnectionCond,
        HvProcess_ChgChargeConnectionAction,
        (uint16)HVPROCESS_CHG_RELAY_OFF_DELAY,
    },
    {
        HvProcess_ChgFaultCond,
        HvProcess_ChgFaultAction,
        (uint16)HVPROCESS_CHG_RELAY_OFF_DELAY,
    }
};

const HvProcess_StateInfoType HvProcess_ChgRelayOffDelayInfoConfig[] = {
    {
        HvProcess_ChgRelayOffDelayCond,
        HvProcess_ChgRelayOffDelayAction,
        (uint16)HVPROCESS_CHG_RESTART,
    }
};

const HvProcess_StateInfoType HvProcess_ChgRestartAllowedInfoConfig[] = {
    {
        HvProcess_ChgRestartAllowedCond,
        NULL,
        (uint16)HVPROCESS_CHG_START,
    }
};

const HvProcess_StateConfigType HvProcess_ChgStateConfig[HVPROCESS_CHG_STATE_MAX] = {
    {
        (uint8)ARRAY_SIZE(HvProcess_ChgStartInfoConfig),
        HvProcess_ChgStartInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_ChgHvOnInfoConfig),
        HvProcess_ChgHvOnInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_ChgRelayOffDelayInfoConfig),
        HvProcess_ChgRelayOffDelayInfoConfig,
    },
    {
        (uint8)ARRAY_SIZE(HvProcess_ChgRestartAllowedInfoConfig),
        HvProcess_ChgRestartAllowedInfoConfig,
    }
};

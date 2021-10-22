/**
 * \file PrechargeM_Lcfg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 预充电管理配置文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170427 |
 */
#include "PrechargeM.h"
#include "RelayM_Lcfg.h"
#include "UserStrategy.h"

const PrechargeM_ConfigInfoType PrechargeM_ConfigInfo[] =
{
{//放电预充
    2U, /**< retryNum: 重试次数 */
    1000U, /**< retryInternal: 预充失败后重试间隔(ms) */
    300U, /**< timeMin: 最小预充时间(ms) */
    3000U, /**< timeout: 预充超时时间(ms) */
    V_TO_100MV(20U), /**< validVoltMin: 最低有效电压 */
    {
        PRECHARGEM_FINISH_TYPE_PERCENT, /**< type: 预充完成条件类型 */
        PERCENT_TO_THOUSAND(90U), /**< value: 预充完成值,若预充类型为延时，此值必须小于“预充超时时间” */
        (Current_CurrentType)CURRENT_INVALID_VALUE, /**< current: 完成电流值(0.1A)，输入CURRENT_INVALID_VALUE时表示不检查电流值 */
    },
    UserStrategy_GetMcuVoltage, /**< getMcuVoltFunc: 获取MCU总压接口 */
    200U, /**< continuousTime: 预充完成持续时间(ms),当finishCond.type为PRECHARGEM_FINISH_TYPE_DELAY时，此值不启作用 */
    5000U, /**< relayOnTimeout: 预充继电器闭合超时(ms) */
    500U, /**< relayOffDelay: 预充继电器断开延时，用于放电闭合后预充延时断开(ms) */
    5000U, /**< dchgRelayOnTimeout: 放电继电器闭合超时(ms) */
    RELAYM_FN_PRECHARGE, /**< prechargeRelayChannel: 预充继电器通道号 */
    RELAYM_FN_POSITIVE_MAIN, /**< dchgRelayChannel: 放电继电器通道号 */
    (Current_CurrentType)CURRENT_INVALID_VALUE, /**< currentMax: 预充最大安全电流(0.1A)，输入CURRENT_INVALID_VALUE时表示不检查电流值 */
    1000U, /**< overCurTime: 允许超预充最大电流最大时间(ms) */
},
{//充电预充
    2U, /**< retryNum: 重试次数 */
    1000U, /**< retryInternal: 预充失败后重试间隔(ms) */
    300U, /**< timeMin: 最小预充时间(ms) */
    3000U, /**< timeout: 预充超时时间(ms) */
    V_TO_100MV(50U), /**< validVoltMin: 最低有效电压 */
    {
        PRECHARGEM_FINISH_TYPE_PERCENT, /**< type: 预充完成条件类型 */
        PERCENT_TO_THOUSAND(96U), /**< value: 预充完成值,若预充类型为延时，此值必须小于“预充超时时间” */
        (Current_CurrentType)CURRENT_INVALID_VALUE, /**< current: 完成电流值(0.1A)，输入CURRENT_INVALID_VALUE时表示不检查电流值 */
    },
    UserStrategy_GetMcuVoltage, /**< getMcuVoltFunc: 获取MCU总压接口 */
    200U, /**< continuousTime: 预充完成持续时间(ms),当finishCond.type为PRECHARGEM_FINISH_TYPE_DELAY时，此值不启作用 */
    5000U, /**< relayOnTimeout: 预充继电器闭合超时(ms) */
    500U, /**< relayOffDelay: 预充继电器断开延时，用于放电闭合后预充延时断开(ms) */
    5000U, /**< dchgRelayOnTimeout: 放电继电器闭合超时(ms) */
    RELAYM_FN_NONE, /**< prechargeRelayChannel: 预充继电器通道号 */
    RELAYM_FN_NONE, /**< dchgRelayChannel: 放电继电器通道号 */
    (Current_CurrentType)CURRENT_INVALID_VALUE, /**< currentMax: 预充最大安全电流(0.1A)，输入CURRENT_INVALID_VALUE时表示不检查电流值 */
    1000U, /**< overCurTime: 允许超预充最大电流最大时间(ms) */
},
};

const uint8 PrechargeM_ConfigInfoSize = (uint8)ARRAY_SIZE(PrechargeM_ConfigInfo);

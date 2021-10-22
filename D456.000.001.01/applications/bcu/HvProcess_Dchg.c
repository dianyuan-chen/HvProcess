/**
 * \file HvProcess_Dchg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压放电流程控制文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */
#include "Cpu.h"
#include "HvProcess_Dchg.h"
#include "HvProcess_Chg.h"
#include "ChargeConnectM.h"
#include "ChargeM.h"
#include "DischargeM.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"
#include "PrechargeM.h"
#include "Statistic.h"

static HvProcess_DchgInnerDataType HvProcess_DchgInnerData;

void HvProcess_DchgInit(Async_LooperType *looper)
{
    (void)looper;
    HvProcess_DchgInnerData.State = HVPROCESS_DCHG_START;
}

HvProcess_DchgStateType HvProcess_GetDchgState(void)
{
    HvProcess_DchgStateType state;
    imask_t mask;

    Irq_Save(mask);
    state = HvProcess_DchgInnerData.State;
    Irq_Restore(mask);

    return state;
}

void HvProcess_SetDchgState(HvProcess_DchgStateType state)
{
    imask_t mask;

    Irq_Save(mask);
    HvProcess_DchgInnerData.State = state;
    Irq_Restore(mask);
}

void HvProcess_DchgPoll(void)
{

}

static boolean HvProcess_DchgRelayIsNormal(void)
{

}


boolean HvProcess_DchgStateStartCond(void)
{

}

void HvProcess_DchgStateStartAction(void)
{

}

boolean HvProcess_DchgStatePrechargeCond(void)
{

}

void HvProcess_DchgStatePrechargeAction(void)
{
    (void)RelayM_Control(RELAYM_FN_POSITIVE_MAIN, RELAYM_CONTROL_ON);
}

boolean HvProcess_DchgChargeConnectionCond(void)
{

}

void HvProcess_DchgChargeConnectionAction(void)
{

}

static const Diagnosis_ItemType items[4U] = {
    DIAGNOSIS_ITEM_DCHG_LTV,
    DIAGNOSIS_ITEM_DCHG_LV,
    DIAGNOSIS_ITEM_VOLT_LINE,
    DIAGNOSIS_ITEM_TEMP_LINE
};

boolean HvProcess_DchgFaultCond(void)
{

}

void HvProcess_DchgFaultAction(void)
{

}

boolean HvProcess_DchgRelayOffDelayCond(void)
{

}

void HvProcess_DchgRelayOffDelayAction(void)
{

}

boolean HvProcess_DchgRestartAllowedCond(void)
{

}

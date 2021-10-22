/**
 * \file HvProcess_Chg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压充电流程控制文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */
#include "stdlib.h"
#include "Cpu.h"
#include "HvProcess_Dchg.h"
#include "HvProcess_Chg.h"
#include "ChargeConnectM.h"
#include "ChargeM.h"
#include "Statistic.h"
#include "DischargeM.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"
#include "ChargerComm.h"
#include "RuntimeM.h"
#include "ChargerCommUser_Messages.h"
#include "UserStrategy.h"
// #include "ChargeM_Cfg.h"
// #include "DischargeM_Cfg.h"

static HvProcess_ChgInnerDataType HvProcess_ChgInnerData;


void HvProcess_ChgInit(Async_LooperType *looper)
{
    (void)looper;
    HvProcess_ChgInnerData.State = HVPROCESS_CHG_START;
}

HvProcess_ChgStateType HvProcess_GetChgState(void)
{
    HvProcess_ChgStateType state;
    imask_t mask;

    Irq_Save(mask);
    state = HvProcess_ChgInnerData.State;
    Irq_Restore(mask);

    return state;
}

void HvProcess_SetChgState(HvProcess_ChgStateType state)
{
    imask_t mask;

    Irq_Save(mask);
    HvProcess_ChgInnerData.State = state;
    Irq_Restore(mask);
}

void HvProcess_ChgPoll(void)
{

}

static boolean HvProcess_ChgRelayIsNormal(void)
{

}

boolean HvProcess_ChgStateStartCond(void)
{

}

void HvProcess_ChgStateStartAction(void)
{

}

boolean HvProcess_ChgIsFinishCond(void)
{

}

void HvProcess_ChgFinishAction(void)
{

}

boolean HvProcess_ChgChargeConnectionCond(void)
{

}

void HvProcess_ChgChargeConnectionAction(void)
{

}
static const Diagnosis_ItemType items[4U] = {
    DIAGNOSIS_ITEM_CHG_HTV,
    DIAGNOSIS_ITEM_CHG_HV,
    DIAGNOSIS_ITEM_VOLT_LINE,
    DIAGNOSIS_ITEM_TEMP_LINE
};

boolean HvProcess_ChgFaultCond(void)
{

}

void HvProcess_ChgFaultAction(void)
{

}

boolean HvProcess_ChgRelayOffDelayCond(void)
{

}

void HvProcess_ChgRelayOffDelayAction(void)
{

}

boolean HvProcess_ChgRestartAllowedCond(void)
{

}

/**
 * \file HvProcess_DC2Chg.c
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 高压DC2充电流程控制文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD00004 | 20170320 |
 */
#include "Cpu.h"
#include "HvProcess_Dchg.h"
#include "HvProcess_DC2Chg.h"
#include "ChargeConnectM.h"
#include "ChargeM.h"
#include "DischargeM.h"
#include "RelayM.h"
// #include "RelayM_Lcfg.h"
#include "ChargerComm.h"
#include "RuntimeM.h"

static HvProcess_DC2ChgInnerDataType HvProcess_DC2ChgInnerData;

void HvProcess_DC2ChgInit(Async_LooperType *looper)
{
    (void)looper;
    HvProcess_DC2ChgInnerData.State = HVPROCESS_DC2CHG_START;
}

HvProcess_DC2ChgStateType HvProcess_GetDC2ChgState(void)
{
    HvProcess_DC2ChgStateType state;
    imask_t mask;

    Irq_Save(mask);
    state = HvProcess_DC2ChgInnerData.State;
    Irq_Restore(mask);

    return state;
}

void HvProcess_SetDC2ChgState(HvProcess_DC2ChgStateType state)
{
    imask_t mask;

    Irq_Save(mask);
    HvProcess_DC2ChgInnerData.State = state;
    Irq_Restore(mask);
}

void HvProcess_DC2ChgPoll(void)
{

}

static Std_ReturnType chgIsReady(void)
{
    Std_ReturnType res = E_NOT_OK;

    if (ChargeM_ChargeIsAllowed() == E_OK)
    {
        if (ChargeM_GetChargerGBReadyStatus(CHARGEM_CHARGERDC2GB_READY_RELAY_INDEX) == CHARGEM_CHARGE_ENABLE)
        {
            res = E_OK;
        }
    }
    return res;
}

static Std_ReturnType chgIsFault(void)
{
    return chgIsReady() == E_OK ? E_NOT_OK : E_OK;
}

boolean HvProcess_DC2ChgStateStartCond(void)
{
    boolean res = FALSE;
    boolean ready;
    Std_ReturnType chargeReady;
    HvProcess_DchgStateType dchgState;

    dchgState = HvProcess_GetDchgState();
    chargeReady = chgIsReady();
    ready = ChargeM_ELIsChargeReady();

    if (CHARGECONNECTM_IS_CONNECT() &&
        dchgState == HVPROCESS_DCHG_START &&
        chargeReady == E_OK &&
        ready)
    {
        res = TRUE;
    }
    return res;
}

void HvProcess_DC2ChgStateStartAction(void)
{
#ifdef RELAYM_FN_POSITIVE_DC2_CHARGE
    (void)RelayM_Control(RELAYM_FN_POSITIVE_DC2_CHARGE, RELAYM_CONTROL_ON);
#endif
}

boolean HvProcess_DC2ChgIsFinishCond(void)
{
    boolean res = FALSE;

    if (ChargeM_BatteryChargeIsFinish() == TRUE)
    {
        res = TRUE;
    }
    return res;
}

void HvProcess_DC2ChgFinishAction(void)
{
    HvProcess_DC2ChgInnerData.RelayOffTick = OSTimeGet();
    HvProcess_DC2ChgInnerData.chgFinishFlag = TRUE;
}

boolean HvProcess_DC2ChgChargeConnectionCond(void)
{
    boolean res = FALSE;

    if (!CHARGECONNECTM_IS_CONNECT())
    {
        res = TRUE;
    }
    return res;
}

void HvProcess_DC2ChgChargeConnectionAction(void)
{
    HvProcess_DC2ChgInnerData.RelayOffTick = OSTimeGet();
}

boolean HvProcess_DC2ChgFaultCond(void)
{
    boolean res = FALSE;

    if (chgIsFault() == E_OK)
    {
        if (HvProcess_DC2ChgIsFinishCond())
        {
            HvProcess_DC2ChgFinishAction();
        }
        res = TRUE;
    }
    return res;
}

void HvProcess_DC2ChgFaultAction(void)
{
    HvProcess_DC2ChgInnerData.RelayOffTick = OSTimeGet();
}

boolean HvProcess_DC2ChgRelayOffDelayCond(void)
{
    boolean res = FALSE;
    uint32 nowTime = OSTimeGet();

    if (MS_GET_INTERNAL(HvProcess_DC2ChgInnerData.RelayOffTick, nowTime) >= 2000U)
    {
        res = TRUE;
        HvProcess_DC2ChgInnerData.RelayOffTick = nowTime;
    }
    return res;
}

void HvProcess_DC2ChgRelayOffDelayAction(void)
{
#ifdef RELAYM_FN_POSITIVE_DC2_CHARGE
    (void)RelayM_Control(RELAYM_FN_POSITIVE_DC2_CHARGE, RELAYM_CONTROL_OFF);
#endif
    if (HvProcess_DC2ChgInnerData.chgFinishFlag == TRUE)
    {
        RuntimeM_RequestPowerDown();
    }
}

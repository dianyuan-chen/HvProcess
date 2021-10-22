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
    boolean res = FALSE;
    if(RELAYM_DIAGNOSIS_IS_NORMAL(RelayM_GetDiagnosisStatus(RELAYM_FN_POSITIVE_MAIN)))
    {
        if(RELAYM_DIAGNOSIS_IS_NORMAL(RelayM_GetDiagnosisStatus(RELAYM_FN_PRECHARGE)))
        {
            if(RELAYM_DIAGNOSIS_IS_NORMAL(RelayM_GetDiagnosisStatus(RELAYM_FN_CHARGE)))
            {
                res = TRUE;
            }
        }
    }
    return res;
}


boolean HvProcess_DchgStateStartCond(void)
{
/*  >判断充电是否已连接，是否唤醒
        >判断充电状态是否在START状态
            >判断继电器故障检查标志 及 现在时间是否大于500
                >继电器故障检查标志置TRUE
                >启动继电器的粘连检测
            >判断故障检查标志是否置TRUE
                    >获取继电器的诊断状态，检查继电器是否正常
                        >判断是否允许放电；检测DCC信号
*/
    boolean res = FALSE;
    uint32 nowTime = OSTimeGet();
    uint8 wakeup = RuntimeM_GetWakeSignal();
    if(!CHARGECONNECTM_IS_CONNECT() && wakeup > 0U)
    {
        if(HvProcess_GetChgState() == HVPROCESS_CHG_START)
        {
            if(!HvProcess_DchgInnerData.RelayFaultCheckFlag && nowTime >= 300U)
            {
                HvProcess_ChgInnerData.RelayFaultCheckFlag == TRUE;
                if(RELAYM_GetActualStatus(RELAYM_FN_POSITIVE_MAIN) == RELAYM_ACTUAL_OFF)
                {
                    if(RELAYM_GetActualStatus(RELAYM_FN_PRECHARGE) == RELAYM_ACTUAL_OFF)
                    {
                        (void)RelayM_StartAdhesiveDetect(RELAYM_FN_POSITIVE_MAIN, NULL);
                        (void)RelayM_StartAdhesiveDetect(RELAYM_FN_PRECHARGE, NULL);
                    }
                }
                if(RELAYM_GetActualStatus(RELAYM_FN_CHARGE) == RELAYM_ACTUAL_OFF)
                {
                    (void)RelayM_StartAdhesiveDetect(RELAYM_FN_CHARGE, NULL);
                }
            }
        }
        if(HvProcess_DchgInnerData.RelayFaultCheckFlag)
        {
            if(HvProcess_DchgRelayIsNormal())
            {
                if(DischargeM_DischargeIsAllowed())
                {
                    res = TRUE;
                }
            }
        }
    }
    return res;
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

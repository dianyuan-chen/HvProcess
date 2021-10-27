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
uint8 pmain = 0, precharge = 0, charge = 0;
uint8 Nmain = 0, Nprecharge = 0, Ncharge = 0;
uint8 normal = 0;
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
    pmain = RelayM_GetDiagnosisStatus(RELAYM_FN_POSITIVE_MAIN);
    precharge = RelayM_GetDiagnosisStatus(RELAYM_FN_PRECHARGE);
    charge = RelayM_GetDiagnosisStatus(RELAYM_FN_CHARGE);
    if(RELAYM_DIAGNOSIS_IS_NORMAL(pmain))
    {
        Nmain = 1U;
        if(RELAYM_DIAGNOSIS_IS_NORMAL(precharge))
        {
            Nprecharge = 1U;
            if(RELAYM_DIAGNOSIS_IS_NORMAL(charge))
            {
                Ncharge = 1U;
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
    Dio_LevelType dccOn = Dio_ReadChannel(DIO_CHANNEL_CHARGER_READY);
    if (!CHARGECONNECTM_IS_CONNECT() && wakeup > 0U)
    {
        if (HvProcess_GetChgState() == HVPROCESS_CHG_START)
        {
            if (!HvProcess_DchgInnerData.RelayFaultCheckFlag && nowTime >= 500UL)
            {
                HvProcess_DchgInnerData.RelayFaultCheckFlag = TRUE;
                if (RelayM_GetActualStatus(RELAYM_FN_POSITIVE_MAIN) == RELAYM_ACTUAL_OFF)
                {
                    if (RelayM_GetActualStatus(RELAYM_FN_PRECHARGE) == RELAYM_ACTUAL_OFF)
                    {
                        (void)RelayM_StartAdhesiveDetect(RELAYM_FN_POSITIVE_MAIN, NULL);
                        (void)RelayM_StartAdhesiveDetect(RELAYM_FN_PRECHARGE, NULL);
                    }
                }
                if (RelayM_GetActualStatus(RELAYM_FN_CHARGE) == RELAYM_ACTUAL_OFF)
                {
                    (void)RelayM_StartAdhesiveDetect(RELAYM_FN_CHARGE, NULL);
                }
                nowTime = OSTimeGet();
            }
            if (HvProcess_DchgInnerData.RelayFaultCheckFlag == TRUE)
            {
                normal = HvProcess_DchgRelayIsNormal();
                if (normal)
                {
                    if (DischargeM_DischargeIsAllowed() == E_OK && dccOn != STD_LOW)
                    {
                        res = TRUE;
                    }
                }
                else
                {
                    if (MS_GET_INTERNAL(nowTime, OSTimeGet()) >= 500U)
                    {
                        HvProcess_DchgInnerData.RelayFaultCheckFlag = FALSE;
                    }
                }
            }
        }
    }

    return res;
}

void HvProcess_DchgStateStartAction(void)
{
    //开始预充
    PrechargeM_Start();
}

boolean HvProcess_DchgStatePrechargeCond(void)
{
    //判断预充是否完成
    boolean res = FALSE;

    if(PrechargeM_IsFinish() == TRUE)
    {
        res = TRUE;
    }

    return res;
}

void HvProcess_DchgStatePrechargeAction(void)
{
    //闭合主正
    (void)RelayM_Control(RELAYM_FN_POSITIVE_MAIN, RELAYM_CONTROL_ON);
}

boolean HvProcess_DchgChargeConnectionCond(void)
{
    /*
    >判断充电是否已连接
    >判断是否有DCC信号
    */
    boolean res = FALSE;

    if(CHARGECONNECTM_IS_CONNECT())
    {
        res = TRUE;
    }
    if(Dio_ReadChannel(DIO_CHANNEL_CHARGER_READY) == STD_LOW)
    {
        res = TRUE;
    }

    return res;
}

void HvProcess_DchgChargeConnectionAction(void)
{
    //置继电器断开时间为当前时间；停止预充
    HvProcess_DchgInnerData.RelayOffTick = OSTimeGet();
    PrechargeM_Stop();
}

static const Diagnosis_ItemType items[4U] = {
    DIAGNOSIS_ITEM_DCHG_LTV,
    DIAGNOSIS_ITEM_DCHG_LV,
    DIAGNOSIS_ITEM_VOLT_LINE,
    DIAGNOSIS_ITEM_TEMP_LINE
};

boolean HvProcess_DchgFaultCond(void)
{
    /*
    >判断是否有放电故障
        >排除指定诊断序列后当前放电故障标志是否成立，若成立，延时为0
        >判断时间是否超过延时
    */
    boolean res = FALSE;
    uint32 nowTime = OSTimeGet() ,delay = 3000UL;
    static uint32 lastTime = 0UL, monitorTime = 0UL;

    if(MS_GET_INTERNAL(monitorTime, nowTime) > 300U)
    {
        lastTime = 0U;
    }
    monitorTime = nowTime;

    if(DischargeM_DischargeIsFault() == E_OK)
    {
        if(DischargeM_DiagnosisIsFaultFlagExcludeItems(items, 4U) == E_OK)
        {
            delay = 0U;
        }
        if(lastTime == 0U)
        {
            lastTime = nowTime;
        }
        if(MS_GET_INTERNAL(lastTime, nowTime) >= delay)
        {
            res = TRUE;
            lastTime = 0U;
        }
    }
    else
    {
        lastTime = 0;
    }

    return res;
}

void HvProcess_DchgFaultAction(void)
{
    //置继电器断开时间为当前时间；停止预充
    HvProcess_DchgInnerData.RelayOffTick = OSTimeGet();
    PrechargeM_Stop();
}

boolean HvProcess_DchgRelayOffDelayCond(void)
{
    //延时500毫秒，置继电器断开时间为当前时间
    boolean res = FALSE;
    uint32 nowTime = OSTimeGet();

    if(MS_GET_INTERNAL(HvProcess_DchgInnerData.RelayOffTick, nowTime) >= 500UL)
    {
        res = TRUE;
        HvProcess_DchgInnerData.RelayOffTick = nowTime;
    }

    return res;
}

void HvProcess_DchgRelayOffDelayAction(void)
{
    /*
        >断开主正
        >置继电器断开时间啊为当前时间
        >置继电器故障检查标志为FALSE
    */
    (void)RelayM_Control(RELAYM_FN_POSITIVE_MAIN, RELAYM_CONTROL_OFF);
    HvProcess_DchgInnerData.RelayOffTick = OSTimeGet();
    HvProcess_DchgInnerData.RelayFaultCheckFlag = FALSE;
}

boolean HvProcess_DchgRestartAllowedCond(void)
{
    /*
        >判断总压是否有效定义
            >判断后端电压是否高于前端电压90%（若高于90%会报粘连故障）,若低于90%，延时2000ms
        >判断是否到达延时时间
    */
    boolean res = FALSE;
    App_Tv100mvType bat_tv = HV_GetVoltage(HV_CHANNEL_BPOS), hv1 = HV_GetVoltage(HV_CHANNEL_HV1), hv2 = HV_GetVoltage(HV_CHANNEL_HV2);
    uint32 delay = 30000UL,nowTime = OSTimeGet();
    static uint32 lastTime = 0UL;

    if (Statistic_TotalVoltageIsValid(bat_tv))
    {
        if (Statistic_TotalVoltageIsValid(hv1))
        {
            if (Statistic_TotalVoltageIsValid(hv2))
            {
                bat_tv = (App_Tv100mvType)((uint32)bat_tv * (uint32)RelayMConfigData[RELAYM_FN_POSITIVE_MAIN].totalPercent / 100UL);
                if (hv1 <= bat_tv && hv2 <= bat_tv)
                {
                    delay = 2000U;
                }
            }
        }
    }
    if(lastTime == 0UL)
    {
        lastTime = nowTime;
    }
    if (MS_GET_INTERNAL(lastTime, nowTime) >= delay)
    {
        lastTime = 0UL;
        res = TRUE;
    }

    return res;
}
